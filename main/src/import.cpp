#include "import.h"
#include "parsemino.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

static Maybe<data> get_mino_data(stringstream& str)
{
	string s;
	vector<string> buffer2;
	while(getline(str,s))
	{
		buffer2.push_back(s);
	}
	return parse_mino(buffer2); 
}

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
		
		stringstream buffer;
		buffer << ifs.rdbuf();
		const Maybe<data>& mD = get_mino_data(buffer);
		if(mD.isNothing())
		{
			ret_val = SOMETHING_WRONG;
			continue;
		}
		st.content[vec[j]] = mD.unJust(); // fixme
		cout << "OK, \"" << vec[j] << "\" loaded." << endl << endl;
	}
	return ret_val;
}
