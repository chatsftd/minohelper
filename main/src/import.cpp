#include "import.h"
#include "parsemino.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

status import_(state& st, const vector<string>& vec)
{
	status ret_val = ALL_OK;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "Loading \"" << vec[j] << "\" ..." << endl;
		ifstream ifs(vec[j].c_str());
		if(!ifs)
		{
			cerr << "file \"" << vec[j] << "\" does not exist" << endl << endl;
			ret_val = NO_FILE; // error
			continue;
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
			ret_val = SOMETHING_WRONG;
			continue;
		}
		st.content[vec[j]] = mD.unJust(); 
		cout << "OK, \"" << vec[j] << "\" loaded." << endl << endl;
	}
	return ret_val;
}
