#include "fileselect.h"
#include "export.h"
#include "parsearg.h"
#include "import.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


static string export4(const mino& m, const color_palette& palette)
{
	stringstream ans;
	ans << '"' << palette.get_color_of(m.ch).to_int();
	ans << '_' << static_cast<int>(m.get_shape_num());
	ans << '_' << "0";
	ans << '_' << m.top_left().second;
	ans << '_' << "0";
	ans << '"';	
	return ans.str();
}

struct mjsn
{
	vector< vector<mino> > inside;
	void make_mjsn(const vector<mino>& minos);
};

void mjsn::make_mjsn(const vector<mino>& minos)
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
	
	
	while(!result.empty()) // remove empty vector<mino>
	{
		if(result.back().empty()) result.pop_back();
		else break;
	}
	
	this->inside = result;
}

static error_level export3(string& str, const vector<mino>& minos, const color_palette& palette)
{
	mjsn m;
	m.make_mjsn(minos);
	vector< vector<mino> > result = m.inside;
	
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

error_level export_(state& st, const arguments2& args)
{
	ret_data ret;
	error_level s2 = ret.parse_arg2(default_arg_info(),args);
	if(s2 != ALL_OK) return s2;
	
	string input  = ret.last_valid("");
	string output = ret.last_valid("-o");
	if(input == "")
	{
		error_level s = file_select(input, st);
		if(s != ALL_OK) return s;
	}
	
	if(st.content.find(input) == st.content.end()) // if input is not found
	{
		/*
		 * create args from thin air and 
		 * import the file
		 */
		
		arguments2 new_args;
		new_args.push_back("import");
		new_args.push_back(input); 
		
		error_level s9 = import_(st,new_args);
		if(s9 != ALL_OK) return s9;
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
	error_level s3 = export3(str,st.content[input].minos,st.content[input].palette);
	if(s3 != ALL_OK) return s3;
	
	ofs << str << endl;
	cout << "Finished." << endl << endl;
	return ALL_OK;
}
