#include "config.h"
#include "parsearg.h"
using namespace std;

status config_(state& st, const arguments2& args)
{
	ret_data ret;
	arg_info info;
	info["--set" ] = 2; // config --set verbosity 3
	info["--get" ] = 1; // config --get verbosity
	info["--list"] = 0; // config --list
	status s2 = ret.parse_arg2(info,args);
	return ALL_OK;
}
