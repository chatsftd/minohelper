#include "fileselect.h"
#include "export.h"
#include "parsearg.h"
#include "import.h"
#include "mjsn.h"
#include "lib/debug.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
using namespace std;

struct mino_map_segment
{
	vector<mino> minos;
	point last_pos;
	direction dir;
	mino_map_segment(vector<mino> m, point p, direction d) : minos(m), last_pos(p), dir(d) {}
};

vector<mino_with_dir> add_dir(const vector<mino>& minos, direction dir)
{
	vector<mino_with_dir> ans;
	for(size_t i = 0; i < minos.size(); i++)
	{
		ans.push_back(mino_with_dir(minos[i],dir));
	}
	return ans;
}

enum merge_status
{
	MERGE_SUCCESS,
	MERGE_CONFLICT,
	MERGE_NOT_FOUND
};

class core
{
	vector<mino_with_dir> inside;
	map<size_t,string> label_table;
	
public:
	core() : inside(), label_table() {}
	core(vector<mino_with_dir> i, map<size_t,string> l) : inside(i), label_table(l) {}
	core(const mino_map_segment& segment, const label_info& labels);
	vector<mino_with_dir> get_inside() const { return this->inside; }
	
	merge_status merge(const core& c);
};

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


static string export3(state::file_data dat)
{
	mjsn m;
	
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
	
	m.make_mjsn(first_segment);
	return m.to_str(dat.palette);
}

error_level export_(state& st, const arguments2& args)
{
	ret_data ret;
	error_level s2 = ret.parse_arg2(default_arg_info(),args);
	if(s2 != ALL_OK) return s2;
	
	string input  = ret.last_valid("");
	string output = ret.last_valid("-o");
	if(input == "")
	{
		error_level s = file_select(input, st);
		if(s != ALL_OK) return s;
	}
	
	if(st.content.find(input) == st.content.end()) // if input is not found
	{
		/*
		 * create args from thin air and 
		 * import the file
		 */
		
		arguments2 new_args;
		new_args.push_back("import");
		new_args.push_back(input); 
		
		error_level s9 = import_(st,new_args);
		if(s9 != ALL_OK) return s9;
	}
	
	if(output == "")
	{
		cout << "To where?" << endl;
		cout << ">>> " << flush;
		getline(cin,output);
	}
	
	ofstream ofs(output.c_str());
	cout << "Exporting \"" << input << "\" to \"" << output << "\" ..." << endl;
	
	
	ofs << export3(st.content[input]) << endl;
	cout << "Finished." << endl << endl;
	return ALL_OK;
}
