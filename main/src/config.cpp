#include "config.h"
#include "parseconfig.h"
#include "parsearg.h"
#include "help.h"
#include "lib/debug.h"
#include "lib/pathroot.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
using namespace std;


static error_level get_all(istream& ifs, map<string,config_value>& list);

static error_level get_data(istream& ifs, const string& name, config_value& num2)
{
	map<string,config_value> list;
	error_level s = get_all(ifs,list);
	if(s != ALL_OK) return s;
	
	if(list.find(name) == list.end()) //not found
	{
		cerr << "Config variable '" << name << "' not found" << endl; cout << endl;
		return CONFIG_VAR_NOT_FOUND;
	}
	
	num2 = list[name];
	return ALL_OK;
}

static error_level get_all(istream& ifs, map<string,config_value>& list)
{
	string str;
	while(getline(ifs, str))
	{
		string vname;
		config_value num;
		parsestat s = parse_line(str,vname,num);
		switch(s)
		{ 
			case EMPTY_LINE: continue;
			case VALID_LINE: list[vname] = num; break;
			case INVALID_LINE:
				cerr << "Config line '" << str << "' is invalid" << endl; cout << endl;
			return CONFIG_FORMAT_WRONG;
		} 
	}
	return ALL_OK;
}

static error_level write_all(ostream& os, const string& path, bool padding)
{
	ifstream ifs(path.c_str());
	if(!ifs)
	{
		cerr << "Unable to read from '" << path << "'" << endl; cout << endl;
		return CONFIG_READ_FAILED;
	}
	map<string,config_value> list;
	error_level s = get_all(ifs,list);
	if(s != ALL_OK) return s;
	for(map<string,config_value>::iterator it = list.begin(); it != list.end(); ++it)
	{
		os << (padding ? "    " : "") << (it->first) << " = " << (it->second) << endl;
	}
	return ALL_OK;
}

error_level config_(state& /*st**/, const arguments2& args)
{
	ret_data ret;
	arg_info info;
	info["--set" ] = 2; // config --set verbosity 3
	info["--get" ] = 1; // config --get verbosity
	info["--list"] = 0; // config --list
	info["--compress"] = 0; // config --compress
	error_level s2 = ret.parse_arg2(info,args);
	if(s2 != ALL_OK) return s2;
	
	const vector<vector<string> > opts = ret.options();
	
	if(opts.empty())
	{
		cout << help_message("config") << endl;
		return ALL_OK;
	}
	
	string path = path_root() + "minohelper_config.txt";
	cout << "File path: " << path << endl;
	
	const vector<string> opt = opts[0];
	if(opt[0] == "--set")
	{
				if(!is_varname(opt[1]))
				{
					cerr << "'" << opt[1] << "' is not a valid name for config variable." << endl; cout << endl;
					return INVALID_ARGS;
				}
				
				stringstream ss(opt[2].c_str());
				config_value num;
				ss >> num;
				if(!ss)
				{
					cerr << "'" << opt[2] << "' is not a valid value for config variable." << endl; cout << endl;
					return INVALID_ARGS;
				}
				
				cout << "set " << opt[1] << " = " << opt[2] << endl << endl;
				ofstream ofs(path.c_str(), ios::out | ios::app);
				if(!ofs)
				{
					cerr << "Unable to write to '" << path << "'" << endl; cout << endl;
					return CONFIG_WRITE_FAILED;
				}
				ofs << '\n' << opt[1] << " = " << opt[2] << endl;
	}
	else if(opt[0] == "--get")
	{
				if(!is_varname(opt[1]))
				{
					cerr << "'" << opt[1] << "' is not a valid name for config variable." << endl; cout << endl;
					return INVALID_ARGS;
				}
				cout << "get " << opt[1] << endl;
				ifstream ifs(path.c_str());
				if(!ifs)
				{
					cerr << "Unable to read from '" << path << "'" << endl; cout << endl;
					return CONFIG_READ_FAILED;
				}
				config_value num;
				error_level s = get_data(ifs,opt[1],num);
				if(s != ALL_OK) return s;
				cout << num << endl << endl;
	}
	else if(opt[0] == "--list")
	{
				cout << "list:" << endl;
		error_level e = write_all(cout,path,true);
		if(e != ALL_OK) return e;
				cout << endl;
	}
	else if(opt[0] == "--compress")
	{
		stringstream ss;
		error_level e = write_all(ss,path,false);
		if(e != ALL_OK) return e;
		
		ofstream ofs(path.c_str(), ios::out);
		if(!ofs)
		{
			cerr << "Unable to write to '" << path << "'" << endl; cout << endl;
			return CONFIG_WRITE_FAILED;
		}
		
		const string str = ss.str(); 
		ofs << str << flush;
		cout << "The config file was successfully compressed." << endl << endl;
	}
	
	return ALL_OK;
}
