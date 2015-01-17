#include "fileselect.h"
#include "export.h"
#include "parsearg.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


static string export4(const mino& m, color_palette palette)
{
	stringstream ans;
	ans << '"' << (palette.exist(m.ch) ? palette.p[m.ch] : palette.default_color).to_int();
	ans << '_' << static_cast<int>(m.get_shape_num());
	ans << '_' << "0";
	ans << '_' << m.top_left().second;
	ans << '_' << "0";
	ans << '"';	
	return ans.str();
}

static status export3(string& str, const vector<mino>& minos, color_palette palette)
{
	size_t down_most = 0;
	for(size_t i = 0; i < minos.size(); ++i) //look for down_most
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
	
	
	for(size_t j = result.size()-1; j >= 0; --j) // remove empty vector<mino>
	{
		if(result[j].empty()) result.pop_back();
		else break;
	}
	
	str = "[\"\",";
	for(size_t j = 0; j < result.size(); ++j)
	{
		if(result[j].empty())
		{
			str += "\"\",";
			continue;
		}
		str += "[";
		
		for(size_t k = 0; k < result[j].size(); ++k)
		{
			str += export4(result[j][k], palette);
			if(k+1 != result[j].size())
			{
				str += ",";
			}
		}
		str += "],";
	}
	str += "\"end\"]";
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
	
	if(output == "")
	{
		cout << "To where?" << endl;
		cout << ">>> " << flush;
		getline(cin,output);
	}
	
	ofstream ofs(output.c_str());
	
	cout << "Exporting \"" << input << "\" to \"" << output << "\" ..." << endl;
		
	string str = "";
	status s3 = export3(str,st.content[input].minos,st.content[input].palette);
	if(s3 != ALL_OK) return s3;
	
	ofs << str << endl;
	cout << "Finished." << endl << endl;
	return ALL_OK;
}
