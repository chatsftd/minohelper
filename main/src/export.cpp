#include "export.h"
#include <iostream>
using namespace std;

static status export2(const string& file, const vector<string>& vec)
{
	cout << "Exporting \"" << file << "\"..." << endl;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "argument #" << j << " is \"" << vec[j] << '"' << endl;
	}
	
	return ALL_OK;
}


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
			
		case 1:
		{ 
			const string& filename = st.content.begin()->first;
			return export2(filename,vec);
			break; // consistency 
		}
		
		default: 
			break;
	}
	
	cout << "Loaded files are:" << endl;
	for(map<string,data>::iterator it = st.content.begin(); it != st.content.end(); ++it)
	{
		cout << '\t' << it->first << endl;
	}
	cout << endl;
	return ALL_OK;
}
