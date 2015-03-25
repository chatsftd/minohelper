#include "mergesegments.h"
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
using namespace std;

struct label_table
{
	std::map<std::string,size_t> inside;
	label_table() : inside() {}
	label_table(std::map<std::string,size_t> i) : inside(i) {}
	bool empty() const { return this->inside.empty(); }
	size_t size() const { return this->inside.size(); }
	void add_offset(int x); 
};


std::set<std::string> common_labels(const label_table& t1, const label_table& t2);

class core
{
	std::vector<mino_with_dir> inside;
	label_table table;
	
public:
	core() : inside(), table() {}
	core(std::vector<mino_with_dir> i, std::map<std::string,size_t> l) : inside(i), table(l) {}
	core(const mino_map_segment& segment, const label_info& labels);
	std::vector<mino_with_dir> get_inside() const { return this->inside; }
	merge_status merge(const core& c);
	core& operator+=(size_t x); 
};

core operator+(core lhs, size_t rhs) { lhs += rhs; return lhs; }


vector<mino_with_dir> add_dir(const vector<mino>& minos, direction dir)
{
	vector<mino_with_dir> ans;
	for(size_t i = 0; i < minos.size(); i++)
	{
		ans.push_back(mino_with_dir(minos[i],dir));
	}
	return ans;
}

void label_table::add_offset(int x)
{
	for(std::map<std::string,size_t>::iterator it = this->inside.begin(); it != this->inside.end(); ++it)
	{
		it->second += x;
	}
}

core::core(const mino_map_segment& segment, const label_info& labels)
{
	vector<mino_with_dir> mds = add_dir(segment.minos,segment.dir);
		
	map<string,size_t> tabl;
	
	typedef multimap<string,label_info::label_content> label_map;
	label_map labels2 = labels.get_labels_from_pos(segment.last_pos);
	for(label_map::const_iterator it = labels2.begin(); it != labels2.end(); ++it)
	{
		tabl[it->first] = it->second.num;
	}
	this->inside = mds;
	this->table = tabl;
}

set<string> common_labels(const label_table& t1, const label_table& t2)
{
	set<string> tmp;
	set<string> res;
	for(map<string,size_t>::const_iterator it = t1.inside.begin(); it != t1.inside.end(); ++it)
	{
		tmp.insert(it->first);
	}
	
	for(map<string,size_t>::const_iterator it = t2.inside.begin(); it != t2.inside.end(); ++it)
	{
		if(tmp.count(it->first)) {	res.insert(it->first);	}
	}
	return res;
}

merge_status core::merge(const core& that)
{
	if(that.inside.empty())
	{
		return MERGE_SUCCESS; //do nothing
	}
	
	if(this->inside.empty())
	{
		core tmp(that); //copy
		*this = tmp;
		return MERGE_SUCCESS;
	}
	
	if(this->table.empty()) return MERGE_NOT_FOUND;
	if( that.table.empty()) return MERGE_NOT_FOUND;
	
	set<string> common_labs = common_labels(this->table,that.table);
	if(common_labs.empty()) return MERGE_NOT_FOUND;
	
	
	string first_label = *(common_labs.begin());
	size_t row1 = this->table.inside.find(first_label)->second; //this->table.inside.at(first_label);
	size_t row2 =  that.table.inside.find(first_label)->second;
	
	core this2 = *this + row2; //criss-cross
	core that2 =  that + row1;

#define all(c) (c).begin(),(c).end()	
	this2.inside.insert(this2.inside.end(), all(that2.inside));	//append
	
	multimap<std::string,size_t> mss;
	mss.insert(all(this2.table.inside));
	mss.insert(all(that2.table.inside));
	//merge all the table
	for(multimap<std::string,size_t>::const_iterator it = mss.begin(); it != mss.end(); ++it)
	{
		if(mss.count(it->first) > 1) //duplicate
		{
			size_t i1 = this2.table.inside[it->first];
			size_t i2 = that2.table.inside[it->first];
			if(i1 == i2) continue;
			else
			{
				cerr << "conflict occurred with '" << it->first << "' "
				"while adjusting '" << first_label << "'" << endl;
				return MERGE_CONFLICT;
			}
		}
	}
	
	map<std::string,size_t> res;
	res.insert(all(mss)); //copy all
	
	this->inside = this2.inside;
	this->table.inside = res;
#undef all
	return MERGE_SUCCESS;
}

core& core::operator+=(size_t x)
{
	for(size_t i = 0; i < this->inside.size(); i++)
	{
		inside[i].first += x;
	}
	this->table.add_offset(x);
	return *this;
}


static error_level merge_segments_core(core& ans, const vector<mino_map_segment>& segments, const label_info& labels)
{
	deque<core> cores;
	for(size_t i = 0; i < segments.size() ; i++)
	{
		cores.push_back(core(segments[i],labels));
	}
	
	ans = cores.front();
	cores.pop_front();
	
	size_t counter = 0;
	const size_t COUNT_MAX = cores.size();
	
	
	while(cores.size())
	{
		core c = cores.front();
		cores.pop_front();
		
		merge_status s = ans.merge(c);
		if(s == MERGE_CONFLICT)
		{
			return DIRECTION_MERGE_CONFLICT;
		}
		else if(s == MERGE_NOT_FOUND)
		{
			cores.push_back(c);
			counter++;
			if(counter >= COUNT_MAX)
			{
				cerr << "Unable to merge all the segments." << endl; cout << endl;
				return DIRECTION_INCOMPLETE_MERGE;
			}
		}
		
		// do nothing when MERGE_SUCCESS
	}
	
	return ALL_OK;
}

error_level merge_segments(vector<mino_with_dir>& mds, const vector<mino_map_segment>& segments, const label_info& labels)
{
	if(segments.empty())
	{
		mds = vector<mino_with_dir>();
		return ALL_OK;
	}
	
	core c;
	error_level e = merge_segments_core(c,segments,labels);
	
	if(e != ALL_OK) return e;
	
	mds = c.get_inside();
	return ALL_OK;
}
