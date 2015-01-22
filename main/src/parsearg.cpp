#include "parsearg.h"
#include <iostream>
using namespace std;

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
