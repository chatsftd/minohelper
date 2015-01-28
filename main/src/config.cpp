#include "config.h"
#include "parsearg.h"
#include "lib/debug.h"
using namespace std;

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
	const vector<string> opt = opts[0];
	
	switch(opt.size())
	{
		case 3: //set
			cout << "set " << opt[1] << " = " << opt[2] << endl << endl;
		break;
		
		case 2: //get
			cout << "get " << opt[1] << endl << endl;
		break;
		
		case 1:
			cout << "list" << endl << endl;
		break;
	}
	
	return ALL_OK;
}
