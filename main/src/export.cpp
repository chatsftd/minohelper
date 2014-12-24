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

static status parse_arg(string& input, string& output, const vector<string>& vec)
{
	bool after_o = false;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		if(after_o)
		{
			output = vec[j];
			after_o = false;
		}
		else if(vec[j] == (string)"-o")
		{
			after_o = true;
		}
		else
		{
			input = vec[j];
		}
	}
	return ALL_OK;
}

status export_(state& st, const vector<string>& vec)
{
	string input, output;
	status s2 = parse_arg(input,output,vec);
	if(s2 != ALL_OK) return s2;
	
	if(input == "")
	{
		status s = file_select(input, st);
		if(s != ALL_OK) return s;
	}
	
	cout << "Exporting \"" << input << "\"..." << endl;
		
	string str = "";
	status s3 = export3(str,st.content[input].minos);
	if(s3 != ALL_OK) return s3;
	
	cout << str << endl << endl;
	return ALL_OK;
}
