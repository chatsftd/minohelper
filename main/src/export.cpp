#include "fileselect.h"
#include "export.h"
#include <iostream>
using namespace std;

static status export2(const string& file, const data& dat, const vector<string>& vec)
{
	cout << "Exporting \"" << file << "\"..." << endl;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "argument #" << j << " is \"" << vec[j] << '"' << endl;
	}
	
	const vector<mino>& minos = dat.minos;
	
	
	size_t down_most = 0;
	for(size_t i = 0; i < minos.size(); ++i)
	{
		point p = minos[i].top_left();
		cout << "mino #" << i+1 << ": [" << p << "] " << minos[i] << endl;
		if(down_most < p.first) down_most = p.first;
	}
	cout << "down_most: " << down_most+1 << endl;
	
	return ALL_OK;
}




status export_(state& st, const vector<string>& vec)
{
	string filename = "";
	status s = file_select(filename, st);
	if(s == ALL_OK)
	{
		return export2(filename, st.content[filename], vec);
	}
	else
	{
		return s; 
	}
}
