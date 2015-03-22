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
		
	map<size_t,string> table;
	
	typedef multimap<string,label_info::label_content> label_map;
	label_map labels2 = labels.get_labels_from_pos(segment.last_pos);
	for(label_map::const_iterator it = labels2.begin(); it != labels2.end(); ++it)
	{
		table[it->second.num] = it->first;
	}
	this->inside = mds;
	this->label_table = table;
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
