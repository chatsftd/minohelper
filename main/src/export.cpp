#include "fileselect.h"
#include "export.h"
#include <iostream>
#include <sstream>
using namespace std;


static status export3(string& str, const vector<mino>& minos)
{
	size_t down_most = 0;
	for(size_t i = 0; i < minos.size(); ++i)
	{
		point p = minos[i].top_left();
		if(down_most < p.first) down_most = p.first;
	}
	
	vector< vector<mino> > result(down_most+1);
	for(size_t i = 0; i < minos.size(); ++i)
	{
		point p = minos[i].top_left();
		result[down_most - p.first].push_back(minos[i]);
	}
	
	stringstream ans;
	ans << "[\"\",";
	for(size_t j = 0; j < result.size(); ++j)
	{
		if(result[j].empty())
		{
			ans << "\"\",";
			continue;
		}
		ans << "[";
		for(size_t k = 0; k < result[j].size(); ++k)
		{
			ans << "\"";
			ans << "0_";
			ans << static_cast<int>(result[j][k].get_shape_num());
			ans << "_0_";
			ans << result[j][k].top_left().second;
			ans << "_0\"";
			if(k+1 != result[j].size())
			{
				ans << ",";
			}
		}
		ans << "],";
	}
	ans << "\"end\"]";
	str = ans.str(); 
	return ALL_OK;
}

status export_(state& st, const vector<string>& vec)
{
	string filename = "";
	status s = file_select(filename, st);
	if(s == ALL_OK)
	{
		cout << "Exporting \"" << filename << "\"..." << endl;
		for(size_t j = 1; j < vec.size(); ++j)
		{
			cout << "argument #" << j << " is \"" << vec[j] << '"' << endl; // fixme: debug
		}
		string str = "";
		status s = export3(str,st.content[filename].minos);
		cout << str << endl << endl;
		return s;
	}
	else
	{
		return s;
	}
}
