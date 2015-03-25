#include "mjsn.h"
#include "lib/debug.h"
#include "segment/mergesegments.h"
#include "anotherconvert.h"
#include <iostream>
#include <deque>
using namespace std;

error_level another_convert(mjsn& m, const state::file_data& dat)
{
	typedef map<point,direction> dirmap_t;
	dirmap_t dir_map = dat.dir.get_all_points();
	vector<mino> minos = dat.minos;
	
	/* classification */
	deque< vector<mino> > minos_separated;
	for(dirmap_t::const_iterator it = dir_map.begin(); it != dir_map.end(); ++it)
	{
		vector<mino> e;
		point p = it->first;
		
		vector<mino>::iterator it2 = minos.begin();
		while (it2 != minos.end())
		{
			if (it2->top_left() < p)
			{
				e.push_back(*it2);
				it2 = minos.erase(it2);
			}
			else{ ++it2; }
		}

		minos_separated.push_back(e);
	}
	minos_separated.push_back(minos);
	/* classification end */
	
	vector<mino_map_segment> segments;
	
	vector<mino_with_dir> first_segment = add_dir(minos_separated.front(),TO_SOUTH);
	minos_separated.pop_front();
	
	
	for(dirmap_t::const_iterator it = dir_map.begin(); it != dir_map.end(); ++it)
	{
		vector<mino> minos2 = minos_separated.front();
		point p = it->first;
		map<point,point> trans = dat.dir.get_transform();
		
		assert2("geraesdfx", trans.count(p));
		
		point p2 = trans[p]; //last_pos
		
		for(size_t i = 0; i < minos2.size(); i++)
		{
			minos2[i] -= p2.first + 1; 
			// it is guaranteed that minos are not on the same line as the direction
		}
		
		segments.push_back(mino_map_segment(minos2,p2,it->second));
		minos_separated.pop_front();
	}
	
	for(size_t i = 0; i < segments.size(); i++)
	{
		cout << "segment after " << segments[i].last_pos << ":" << endl;
		
		for(size_t j = 0; j < segments[i].minos.size(); j++)
		{
			cout << "    " << segments[i].minos[i] << endl;
		}
	} 
	
	
	vector<mino_with_dir> merged = merge_segments(segments,dat.labels);
	
	if(merged.empty())
	{
		m.make_mjsn(first_segment);
	}
	else if(first_segment.empty())
	{
		m.make_mjsn(merged);
	}
	else
	{
		return BEFORE_AFTER_DIRECTION;
	}
	
	return ALL_OK;
}
