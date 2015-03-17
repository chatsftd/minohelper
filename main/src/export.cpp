#include "fileselect.h"
#include "export.h"
#include "parsearg.h"
#include "import.h"
#include "mjsn.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


static string export3(state::file_data dat)
{
	mjsn m;
	
	typedef map<point,direction> dirmap_t;
	const dirmap_t& dir_map = dat.dir.get_all_points();
	vector<mino> minos = dat.minos;
	
	/* classification */
	vector< vector<mino> > minos_separated;
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
				cout << *it2 << " is before " << p << endl;
				it2 = minos.erase(it2);
			}
			else{ ++it2; }
		}

		minos_separated.push_back(e);
	}
	minos_separated.push_back(minos);
	/* classification end */
	
	m.make_mjsn(dat.minos);
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
