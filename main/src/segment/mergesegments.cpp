#include "mergesegments.h"
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
using namespace std;

typedef map<string,size_t> label_table;


set<string> common_labels(const label_table& t1, const label_table& t2);

class core
{
	vector<mino_with_dir> mds;
	label_table table;
	
public:
	core() : mds(), table() {}
	core(vector<mino_with_dir> i, label_table l) : mds(i), table(l) {}
	core(const mino_map_segment& segment, const label_info& labels);
	vector<mino_with_dir> get_mds() const { return this->mds; }
	merge_status merge(const core& c);
	core& operator+=(size_t x);
};

core operator+(core lhs, size_t rhs) { lhs += rhs; return lhs; }


vector<mino_with_dir> add_dir(const vector<mino>& minos, direction dir)
{
	vector<mino_with_dir> ans;
	for(size_t i = 0; i < minos.size(); i++) {
		ans.push_back(mino_with_dir(minos[i],dir));
	}
	return ans;
}

void add_offset(label_table& t1, int x)
{
	for(label_table::iterator it = t1.begin(); it != t1.end(); ++it) {
		it->second += x;
	}
}

core::core(const mino_map_segment& segment, const label_info& labels)
{
	this->mds = add_dir(segment.minos,segment.dir);
	
	map<string,size_t> tabl;
	
	typedef multimap<string,label_info::label_content> label_map;
	label_map labels2 = labels.get_labels_from_pos(segment.last_pos);
	for(label_map::const_iterator it = labels2.begin(); it != labels2.end(); ++it) {
		tabl[it->first] = it->second.num;
	}
	this->table = tabl;
}

set<string> common_labels(const label_table& t1, const label_table& t2)
{
	set<string> tmp;
	set<string> res;
	for(map<string,size_t>::const_iterator it = t1.begin(); it != t1.end(); ++it) {
		tmp.insert(it->first);
	}
	
	for(map<string,size_t>::const_iterator it = t2.begin(); it != t2.end(); ++it) {
		if(tmp.count(it->first)) {	res.insert(it->first);	}
	}
	return res;
}

merge_status core::merge(const core& that)
{
	if(that.mds.empty()) {
		return MERGE_SUCCESS; //do nothing
	}
	
	if(this->mds.empty()) {
		core tmp(that); //copy
		*this = tmp;
		return MERGE_SUCCESS;
	}
	
	if(this->table.empty()) return MERGE_NOT_FOUND;
	if( that.table.empty()) return MERGE_NOT_FOUND;
	
	set<string> common_labs = common_labels(this->table,that.table);
	if(common_labs.empty()) return MERGE_NOT_FOUND;
	
	
	string first_label = *(common_labs.begin());
	size_t row1 = this->table.find(first_label)->second; //this->table.at(first_label);
	size_t row2 =  that.table.find(first_label)->second;
	
	core this2 = *this + row2; //criss-cross
	core that2 =  that + row1;
	
#define all(c) (c).begin(),(c).end()
	this2.mds.insert(this2.mds.end(), all(that2.mds));	//append
	
	multimap<string,size_t> mss;
	mss.insert(all(this2.table));
	mss.insert(all(that2.table));
	//merge all the table
	for(multimap<string,size_t>::const_iterator it = mss.begin(); it != mss.end(); ++it) {
		if(mss.count(it->first) > 1) { //duplicate
			size_t i1 = this2.table[it->first];
			size_t i2 = that2.table[it->first];
			if(i1 == i2) continue;
			else {
				cerr << "conflict occurred with '" << it->first << "' "
				     "while adjusting '" << first_label << "'" << endl;
				return MERGE_CONFLICT;
			}
		}
	}
	
	map<string,size_t> res;
	res.insert(all(mss)); //copy all
	
	this->mds = this2.mds;
	this->table = res;
#undef all
	return MERGE_SUCCESS;
}

core& core::operator+=(size_t x)
{
	for(size_t i = 0; i < this->mds.size(); i++) {
		this->mds[i].first += x;
	}
	add_offset(this->table,x);
	return *this;
}


static error_level merge_segments_core(core& ans, const vector<mino_map_segment>& segments, const label_info& labels)
{
	deque<core> cores;
	for(size_t i = 0; i < segments.size() ; i++) {
		cores.push_back(core(segments[i],labels));
	}
	
	ans = cores.front();
	cores.pop_front();
	
	size_t counter = 0;
	const size_t COUNT_MAX = cores.size();
	
	
	while(cores.size()) {
		core c = cores.front();
		cores.pop_front();
		
		merge_status s = ans.merge(c);
		if(s == MERGE_CONFLICT) {
			return DIRECTION_MERGE_CONFLICT;
		} else if(s == MERGE_NOT_FOUND) {
			cores.push_back(c);
			counter++;
			if(counter >= COUNT_MAX) {
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
	if(segments.empty()) {
		mds = vector<mino_with_dir>();
		return ALL_OK;
	}
	
	core c;
	error_level e = merge_segments_core(c,segments,labels);
	
	if(e != ALL_OK) return e;
	
	mds = c.get_mds();
	return ALL_OK;
}
