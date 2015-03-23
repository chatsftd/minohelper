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

merge_status core::merge(const core& c)
{
	//FIXME
	return MERGE_SUCCESS;
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
