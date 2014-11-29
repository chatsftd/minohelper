#include "import.h"
#include "parsemino.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

static status import_file(state& st, const string& filename)
{
	cout << "Loading \"" << filename << "\" ..." << endl;
	ifstream ifs(filename.c_str());
	if(!ifs)
	{
		cerr << "file \"" << filename << "\" does not exist" << endl << endl;
		return NO_FILE; // error
	}
	
	vector<string> plane;
	{
		string s;
		stringstream buffer;
		buffer << ifs.rdbuf();
		while(getline(buffer,s))
		{
			plane.push_back(s);
		}
	}
	const Maybe<data>& mD = parse_mino(plane); 
	
	if(mD.isNothing())
	{
		return SOMETHING_WRONG;
	}
	st.content[filename] = mD.unJust(); 
	cout << "OK, \"" << filename << "\" loaded." << endl << endl;
	return ALL_OK;
}


status import_(state& st, const vector<string>& vec)
{
	status ret_val = ALL_OK;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		status s = import_file(st,vec[j]);
		if(ret_val == ALL_OK)
		{
			ret_val = s; // return the first error code
		}
	}
	return ret_val;
}
