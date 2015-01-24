#include "parsearg.h"
#include <iostream>
using namespace std;

string last_valid(std::vector<std::vector<std::string> > dat)
{
	string ans = "";
	for(size_t i = 0; i < dat.size(); i++)
	{
		for(size_t j = 0; j < dat[i].size(); j++)
		{
			ans = dat[i][j];
		}
	}
	return ans;
}

arg_info default_arg_info()
{
	arg_info this_;
	this_["-o"] = 1;
	return this_;
}

status parse_arg2(const arg_info& info, ret_data& ret, const arguments2& args)
{
	string opt_now = "";
	size_t count = 0;
	for(size_t j = 1; j < args.size(); ++j)
	{
		if(args[j][0] == '-') //option
		{
			if(count)
			{
				cerr << "Invalid arguments: Encountered option '" << args[j] << "' while parsing option '" << opt_now << "'" << endl; cout << endl;
				return INVALID_ARGS;
			}
			if(info.find(args[j]) == info.end()) //unknown option
			{
				cerr << "Invalid arguments: Encountered unknown option '" << args[j] << "'" << endl; cout << endl;
				return INVALID_ARGS;
			}
			
			count = info.find(args[j])->second; // means `info[args[j]]`
			if(count)
			{
				opt_now = args[j];
				vector<string> vec;
				ret[opt_now].push_back(vec);
			}
			
		}
		else //not option
		{
			if(count)
			{
				ret[opt_now].back().push_back(args[j]);
				count--;
				if(count == 0) opt_now = "";
			}
			else
			{
				vector<string> vec;
				vec.push_back(args[j]);
				ret[opt_now].push_back(vec);
			}
			
		}
		
	}
	return ALL_OK;
}

status parse_arg(string& input, string& output, const arguments2& args)
{
	bool after_o = false;
	for(size_t j = 1; j < args.size(); ++j)
	{
		if(after_o)
		{
			output = args[j];
			after_o = false;
		}
		else if(args[j] == (string)"-o")
		{
			after_o = true;
		}
		else
		{
			input = args[j];
		}
	}
	if(after_o)
	{
		cerr << "Invalid arguments: No file name after '-o'" << endl; cout << endl;
		return INVALID_ARGS;
	}
	return ALL_OK;
}
