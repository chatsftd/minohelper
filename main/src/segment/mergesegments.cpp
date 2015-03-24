#include "mergesegments.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
using namespace std;

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


static core merge_segments_core(const vector<mino_map_segment>& segments, const label_info& labels)
{
	vector<core> cores;
	for(size_t i = 0; i < segments.size() ; i++)
	{
		cores.push_back(core(segments[i],labels));
	}

}

vector<mino_with_dir> merge_segments(const vector<mino_map_segment>& segments, label_info labels)
{
	return merge_segments_core(segments,labels).get_inside();
}
