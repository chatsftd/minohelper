#include "export.h"
#include <iostream>
using namespace std;

status export_(state& st, const vector<string>& vec)
{
	cout << "command \"export\" was called." << endl;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "argument #" << j << " is \"" << vec[j] << '"' << endl;
	}
	
	cout << "Loaded files are:" << endl;
	for(map<string,data>::iterator it = st.content.begin(); it != st.content.end(); ++it)
	{
		cout << '\t' << it->first << endl;
	}
	cout << endl;
	return ALL_OK;
}
