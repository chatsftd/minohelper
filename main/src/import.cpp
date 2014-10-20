#include "import.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

status import_(state st, const vector<string>& vec)
{
	cout << "command \"import\" was called." << endl;
	
	status ret_val = ALL_OK;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "argument #" << j << " is \"" << vec[j] << '"' << endl;
		ifstream ifs(vec[j].c_str());
		if(!ifs)
		{
			cerr << "file \"" << vec[j] << "\" does not exist" << endl << endl;
			ret_val = SOMETHING_WRONG; // error
			continue;
		}
		
		
		
		stringstream buffer;
		buffer << ifs.rdbuf();
		string content = buffer.str();
		st.content[vec[j]] = content;
		cout << "ok, \"" << vec[j] << "\" loaded." << endl;
	}
	return ret_val;
}
