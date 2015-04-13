#include "parsearg.h"
#include <iostream>
using namespace std;

arg_info default_arg_info()
{
	arg_info this_;
	this_["-o"] = 1;
	return this_;
}

vector<vector<string> > ret_data::options(const std::string& opt) const
{
	vector<vector<string> > dat = this->options_;
	vector<vector<string> > ans;
	for(size_t i = 0; i < dat.size(); i++) {
		if(dat[i][0] != opt) continue;
		ans.push_back(dat[i]);
	}
	return ans;
}

vector<vector<string> > ret_data::options() const
{
	return this->options_;
}

error_level ret_data::parse_arg2(const arg_info& info, const arguments2& args)
{
	string opt_now = "";
	size_t count = 0;
	for(size_t j = 1; j < args.size(); ++j) {
		if(args[j][0] == '-') { //option
			if(count) {
				cerr << "Invalid arguments: Encountered option '" << args[j] << "' while parsing option '" << opt_now << "'" << endl; cout << endl;
				return INVALID_ARGS;
			}
			if(info.find(args[j]) == info.end()) { //unknown option
				cerr << "Invalid arguments: Encountered unknown option '" << args[j] << "'" << endl; cout << endl;
				return INVALID_ARGS;
			}
			
			count = info.at(args[j]);
			vector<string> vec;
			vec.push_back(args[j]);
			this->options_.push_back(vec);
			if(count) { opt_now = args[j]; }
			
		} else { //not option
			if(count) {
				this->options_.back().push_back(args[j]);
				count--;
				if(count == 0) opt_now = "";
			} else {
				vector<string> vec;
				vec.push_back("");
				vec.push_back(args[j]);
				this->options_.push_back(vec);
			}
			
		}
		
	}
	if(count != 0) {
		cerr << "Invalid arguments: Encountered end of line while parsing option '" << opt_now << "'" << endl; cout << endl;
		return INVALID_ARGS;
	}
	return ALL_OK;
}
