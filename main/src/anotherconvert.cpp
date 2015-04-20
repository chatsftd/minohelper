#include "mjsn.h"
#include "lib/debug.h"
#include "segment/mergesegments.h"
#include "anotherconvert.h"
#include <iostream>
#include <deque>
using namespace std;
typedef map<point,direction> dirmap_t;
deque< vector<mino> > separate_minos(const dirmap_t& dir_map, vector<mino>/*copy*/ minos)
{
	deque< vector<mino> > ans;
	for(const auto& pa : dir_map) {
		vector<mino> e;
		point p = pa.first;
		
		vector<mino>::iterator it2 = minos.begin();
		while (it2 != minos.end()) {
			if (it2->top_left() < p) {
				e.push_back(*it2);
				it2 = minos.erase(it2);
			} else { ++it2; }
		}
		
		ans.push_back(e);
	}
	ans.push_back(minos);
	return ans;
}

vector<mino_map_segment> make_segments(const dirmap_t& dir_map, const map<point,point>& trans, deque< vector<mino> >/*copy*/ minos_separated)
{
	vector<mino_map_segment> segments;
	for(const auto& pa : dir_map) {
		vector<mino> minos2 = minos_separated.front();
		point p = pa.first;
		
		assert2("geraesdfx", trans.count(p)); //fixme: this assertion can be removed by changing the data structure
		point p2 = trans.at(p); //last_pos
		
		for(size_t i = 0; i < minos2.size(); i++) {
			minos2[i] -= p2.row + 1;
			// it is guaranteed that minos are not on the same line as the direction
		}
		
		segments.push_back(mino_map_segment(minos2,p2,pa.second));
		minos_separated.pop_front();
	}
	return segments;
}

error_level another_convert(mjsn& m, const state::file_data& dat)
{
	dirmap_t dir_map = dat.st2.dir.get_all_points();
	deque< vector<mino> > minos_separated = separate_minos(dir_map, dat.minos);
	vector<mino_with_dir> first_segment = add_dir(minos_separated.front(),TO_SOUTH); // first segment is special; it has no `direction` meta and no label
	minos_separated.pop_front();
	
	vector<mino_map_segment> segments = make_segments(dir_map, dat.st2.dir.get_transform(), minos_separated);
	for(size_t i = 0; i < segments.size(); i++) {
		cout << "segment after " << segments[i].last_pos << ":" << endl;
		
		for(size_t j = 0; j < segments[i].minos.size(); j++) {
			cout << "    " << segments[i].minos[j] << endl;
		}
	}
	
	vector<mino_with_dir> merged;
	error_level e2 = merge_segments(merged,segments,dat.st2.labels);
	
	if(e2 != ALL_OK) return e2;
	
	if(merged.empty()) {
		m.make_mjsn(first_segment);
	} else if(first_segment.empty()) {
		m.make_mjsn(merged);
	} else {
		return BEFORE_AFTER_DIRECTION;
	}
	
	return ALL_OK;
}
