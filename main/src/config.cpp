#include "config.h"
#include "parsearg.h"
#include "lib/debug.h"
#include "lib/pathroot.h"
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;

static inline bool is_varname_init_char(char a){ return isalpha(a) || (a == '_'); }
static inline bool is_varname_more_char(char a){ return isalnum(a) || (a == '_') || (a == '.'); }

enum parsestat
{
	EMPTY_LINE,
	VALID_LINE,
	INVALID_LINE
};

static parsestat parse_line(const string& str, string& varname, int& num)
{
	size_t pos = 0;
	varname = "";
	const static string empty = "";
	if(str.size() == 0){ return EMPTY_LINE; }
	
	while(true) // before varname
	{
		if(!isspace(str[pos])) break;
		pos++;
		if(pos >= str.size()) return EMPTY_LINE;
	}
	
	char init_char = str[pos];
	if(!is_varname_init_char(init_char)){return INVALID_LINE;} 
	varname += empty + init_char;
	pos++;
	if(pos >= str.size()){return INVALID_LINE;} 
	
	while(true)
	{
		char a = str[pos];
		if(!is_varname_more_char(str[pos])) break;
		pos++;
		varname += empty + a;
		if(pos >= str.size()){return INVALID_LINE;} 
	}
	
	while(true) // after varname
	{
		if(!isspace(str[pos])) break;
		pos++;
		if(pos >= str.size()){return INVALID_LINE;} 
	}
	
	if(str[pos++] != '='){return INVALID_LINE;} 
	if(pos >= str.size()){return INVALID_LINE;} 
	
	string leftover = str.substr(pos);
	stringstream ss(leftover.c_str());
	ss >> num;
	if(!ss){return INVALID_LINE;} 
	return VALID_LINE;
	
}

static status get_data(istream& ifs, const string& name, int& num2)
{
	bool is_set = false;
	string str;
	
	while(getline(ifs, str))
	{
		string vname;
		int num;
		parsestat s = parse_line(str,vname,num);
		switch(s)
		{ 
			case EMPTY_LINE: continue;
			case VALID_LINE:
				if(vname == name)
				{
					num2 = num;
					is_set = true;
				}
			break;
			case INVALID_LINE:
				cerr << "Config line '" << str << "' is invalid" << endl; cout << endl;
			return CONFIG_FORMAT_WRONG;
				
		} 
	}
	if(is_set){ return ALL_OK; }
	else
	{
		cerr << "Config '" << name << "' not found" << endl; cout << endl;
		return CONFIG_VAR_NOT_FOUND;
	}
}

status config_(state& st, const arguments2& args)
{
	ret_data ret;
	arg_info info;
	info["--set" ] = 2; // config --set verbosity 3
	info["--get" ] = 1; // config --get verbosity
	info["--list"] = 0; // config --list
	status s2 = ret.parse_arg2(info,args);
	if(s2 != ALL_OK) return s2;
	
	const vector<vector<string> > opts = ret.options();
	
	if(opts.empty())
	{
		cout << "__HELP__CONFIG__" << endl << endl; //fixme
		return ALL_OK;
	}
	
	string path = path_root() + "minohelper_config.txt";
	cout << "File path: " << path << endl;
	
	const vector<string> opt = opts[0];
	
	switch(opt.size())
	{
		case 3: //set
			{
				//fixme: check if opt[1] and opt[2] are valid
				cout << "set " << opt[1] << " = " << opt[2] << endl << endl;
				ofstream ofs(path.c_str(), ios::out | ios::app);
				if(!ofs)
				{
					cerr << "Unable to write to '" << path << "'" << endl; cout << endl;
					return CONFIG_WRITE_FAILED;
				}
				ofs << '\n' << opt[1] << " = " << opt[2] << endl;
			}
		break;
		
		case 2: //get
			{
				//fixme: check if opt[1] is valid
				cout << "get " << opt[1] << endl;
				ifstream ifs(path.c_str());
				if(!ifs)
				{
					cerr << "Unable to read from '" << path << "'" << endl; cout << endl;
					return CONFIG_READ_FAILED;
				}
				int num;
				status s = get_data(ifs,opt[1],num);
				if(s != ALL_OK) return s;
				cout << num << endl << endl;
			}
		break;
		
		case 1:
			cout << "list" << endl << endl;
		break;
	}
	
	return ALL_OK;
}
