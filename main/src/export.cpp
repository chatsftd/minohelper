#include "export.h"
#include <iostream>
using namespace std;

status export_(state& st, const vector<string>& vec)
{
	cout << "command \"export\" was called." << endl;
	size_t size = st.content.size();
	
	switch(size)
	{
		case 0:	
			cout << "No files loaded." << endl << endl;	
			return SOMETHING_WRONG;	
			break; // consistency 
			
		default: 
			break;
	}

	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "argument #" << j << " is \"" << vec[j] << '"' << endl;
	}
	
	cout << (size == 1 ? "Loaded file is:" : "Loaded files are:") << endl;
	for(map<string,data>::iterator it = st.content.begin(); it != st.content.end(); ++it)
	{
		cout << '\t' << it->first << endl;
	}
	cout << endl;
	return ALL_OK;
}
