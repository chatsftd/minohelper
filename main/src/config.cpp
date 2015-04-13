#include "config.h"
#include "config/parseconfig.h"
#include "parsearg.h"
#include "help.h"
#include "lib/debug.h"
#include "lib/pathroot.h"
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

static error_level get_all(istream& ifs, map<string,config_value>& list)
{
	string str;
	while(getline(ifs, str)) {
		string vname;
		config_value val;
		parsestat s = parse_line(str,vname,val);
		switch(s) {
		case EMPTY_LINE: continue;
		case VALID_LINE: list[vname] = val; break;
		case DELETION_LINE: list.erase(vname); break;
		case INVALID_LINE:
			cerr << "Config line '" << str << "' is invalid" << endl; cout << endl;
			return CONFIG_FORMAT_WRONG;
		}
	}
	return ALL_OK;
}

static error_level get_data(istream& ifs, const string& name, config_value& num2)
{
	map<string,config_value> list;
	error_level s = get_all(ifs,list);
	if(s != ALL_OK) return s;
	
	if(list.find(name) == list.end()) { //not found
		cerr << "Config variable '" << name << "' not found" << endl; cout << endl;
		return CONFIG_VAR_NOT_FOUND;
	}
	
	num2 = list[name];
	return ALL_OK;
}

static error_level write_all(ostream& os, const string& path, bool padding)
{
	ifstream ifs(path.c_str());
	if(!ifs) {
		cerr << "Unable to read from '" << path << "'" << endl; cout << endl;
		return CONFIG_READ_FAILED;
	}
	map<string,config_value> list;
	error_level s = get_all(ifs,list);
	if(s != ALL_OK) return s;
	for(const auto& pa : list) {
		os << (padding ? "    " : "") << pa.first << " = " << pa.second << endl;
	}
	return ALL_OK;
}

error_level config_(state& /*st**/, const arguments2& args)
{
	parsed_args ret;
	arg_info info;
	info["--set"     ] = 2; // config --set verbosity 3
	info["--get"     ] = 1; // config --get verbosity
	info["--delete"  ] = 1; // config --delete verbosity
	info["--list"    ] = 0;
	info["--compress"] = 0;
	error_level s2 = ret.parse_arg2(info,args);
	if(s2 != ALL_OK) return s2;
	
	const vector<vector<string> > opts = ret.options();
	
	bool valid_option_exists = false;
	for(size_t i = 0; i < opts.size(); i++) {
		if(opts[i][0] != "") valid_option_exists = true;
	}
	if(!valid_option_exists) {
		cout << help_message("config") << endl;
		return ALL_OK;
	}
	
	string path = path_root() + "minohelper_config.txt";
	cout << "File path: " << path << endl;
	
	for(size_t i = 0; i < opts.size(); i++) {
		const vector<string> opt = opts[i];
		if(opt[0] == "--set") {
			if(!is_varname(opt[1])) {
				cerr << "'" << opt[1] << "' is not a valid name for config variable." << endl; cout << endl;
				return INVALID_ARGS;
			}
			
			stringstream ss(opt[2].c_str());
			config_value val;
			ss >> val;
			if(!ss) {
				cerr << "'" << opt[2] << "' is not a valid value for config variable." << endl; cout << endl;
				return INVALID_ARGS;
			}
			
			ofstream ofs(path.c_str(), ios::out | ios::app);
			if(!ofs) {
				cerr << "Unable to write to '" << path << "'" << endl; cout << endl;
				return CONFIG_WRITE_FAILED;
			}
			ofs << '\n' << opt[1] << " = " << opt[2] << endl;
			
			
			cout << "set " << opt[1] << " = " << opt[2] << endl;
		} else if(opt[0] == "--delete") {
			if(!is_varname(opt[1])) {
				cerr << "'" << opt[1] << "' is not a valid name for config variable." << endl; cout << endl;
				return INVALID_ARGS;
			}
			
			ofstream ofs(path.c_str(), ios::out | ios::app);
			if(!ofs) {
				cerr << "Unable to write to '" << path << "'" << endl; cout << endl;
				return CONFIG_WRITE_FAILED;
			}
			ofs << '\n' << '~' << opt[1] << endl;
			
			cout << "delete " << opt[1] << endl;
		} else if(opt[0] == "--get") {
			if(!is_varname(opt[1])) {
				cerr << "'" << opt[1] << "' is not a valid name for config variable." << endl; cout << endl;
				return INVALID_ARGS;
			}
			cout << "get " << opt[1] << endl;
			ifstream ifs(path.c_str());
			if(!ifs) {
				cerr << "Unable to read from '" << path << "'" << endl; cout << endl;
				return CONFIG_READ_FAILED;
			}
			config_value val;
			error_level s = get_data(ifs,opt[1],val);
			if(s != ALL_OK) return s;
			cout << val << endl;
		} else if(opt[0] == "--list") {
			cout << "list:" << endl;
			error_level e = write_all(cout,path,true);
			if(e != ALL_OK) return e;
		} else if(opt[0] == "--compress") {
			stringstream ss;
			error_level e = write_all(ss,path,false);
			if(e != ALL_OK) return e;
			
			ofstream ofs(path.c_str(), ios::out);
			if(!ofs) {
				cerr << "Unable to write to '" << path << "'" << endl; cout << endl;
				return CONFIG_WRITE_FAILED;
			}
			
			const string str = ss.str();
			ofs << str << flush;
			cout << "The config file was successfully compressed." << endl;
		}
		cout << endl;
		
	}
	return ALL_OK;
}
