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

static status file_select(string& filename, const state& st)
{
	size_t size = st.content.size();
	
	switch(size)
	{
		case 0:	
			cout << "No files loaded." << endl << endl;	
			return SOMETHING_WRONG;	
			break; // consistency 
			
		case 1:
			filename = st.content.begin()->first;
			return ALL_OK;
			break; // consistency 
		
		default: 
			break;
	}
	
	cout << "Which file?" << endl;
	typedef size_t Index;
	
	Index i = 1;
	map<Index, string> map_;
	for(map<string,data>::const_iterator it = st.content.begin(); it != st.content.end(); ++it)
	{
		cout << '\t' << i << ": \"" << it->first << '"' << endl;
		map_[i] = it->first;
		i++;
	}
	Index max_plus_1 = i;
	
	cout << ">>> " << flush;
	
	string str;
	getline(cin, str);
	
	stringstream s2(str.c_str());
	Index inp;
	s2 >> inp;
	if(inp == 0 || inp >= max_plus_1)
	{
		cout << "No such index." << endl;
		return SOMETHING_WRONG;
	}
	else
	{
		filename = map_[inp];
		return ALL_OK;
	}
}


status export_(state& st, const vector<string>& vec)
{
	string filename = "";
	status s = file_select(filename, st);
	if(s == ALL_OK)
	{
		return export2(filename,vec);
	}
	else
	{
		return s; 
	}
}
