#include "import.h"
#include "parsemino.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

static data get_mino_data(stringstream& str)
{
	string s;
	vector<string> buffer2;
	while(getline(str,s))
	{
		buffer2.push_back(s);
	}
	return parse_mino(buffer2); 
}

status import_(state st, const vector<string>& vec)
{
	status ret_val = ALL_OK;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "Loading \"" << vec[j] << "\" ..." << endl;
		ifstream ifs(vec[j].c_str());
		if(!ifs)
		{
			cerr << "file \"" << vec[j] << "\" does not exist" << endl << endl;
			ret_val = SOMETHING_WRONG; // error
			continue;
		}
		
		stringstream buffer;
		buffer << ifs.rdbuf();
		st.content[vec[j]] = get_mino_data(buffer);
		cout << "OK, \"" << vec[j] << "\" loaded." << endl;
	}
	return ret_val;
}
