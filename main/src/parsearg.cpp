#include "parsearg.h"
#include <iostream>
using namespace std;

status parse_arg(string& input, string& output, const arguments2& vec)
{
	bool after_o = false;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		if(after_o)
		{
			output = vec[j];
			after_o = false;
		}
		else if(vec[j] == (string)"-o")
		{
			after_o = true;
		}
		else
		{
			input = vec[j];
		}
	}
	if(after_o)
	{
		cerr << "Invalid arguments: No file name after '-o'" << endl; cout << endl;
		return INVALID_ARGS;
	}
	return ALL_OK;
}
