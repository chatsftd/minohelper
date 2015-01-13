#include "import.h"
#include "parsemino.h"
#include "interpretmeta.h"
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
		cerr << "File \"" << filename << "\" does not exist." << endl; cout << endl;
		return INVALID_FILEPATH;
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
	state2 st2;
	status s = interpretmeta(st2,plane);
	if(s != ALL_OK) return s;
	
	const Maybe<data>& mD = parse_mino(st2,plane);
	
	if(mD.isNothing())
	{
		return SOMETHING_WRONG; // ?
	}
	st.content[filename] = mD.unJust();
	cout << "OK, \"" << filename << "\" loaded." << endl << endl;
	return ALL_OK;
}


status import_(state& st, const vector<string>& vec)
{
	status ret_val = ALL_OK;
	if(vec.size() < 2)
	{
		string str;
		cout << "File name?" << endl;
		cout << ">>> " << flush;
		getline(cin,str);
		return import_file(st,str);
	}
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
