#include "fileselect.h"
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
