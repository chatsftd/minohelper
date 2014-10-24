#include "interpret.h"
#include "import.h"
#include "export.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

static void parse(vector<string>& vec, const string& a)
{
	stringstream input;
	input.str(a);
	string b; 
	while(input >> b)
	{
		vec.push_back(b);
	}
}

status interpret(state st, const string& a)
{
	vector<string> vec;
	parse(vec,a);
	
	if(vec.empty()){return ALL_OK;}
#define if2(a) if(vec[0] == string(a))	
	if2("exit")
	{
		return EXIT_ALL;
	}
	else if2("import")
	{
		return import_(st,vec);
	}
	else if2("export")
	{
		return export_(st,vec);
	}
	else
	{
		int j=0;
		for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it,++j)
		{
			cout << "input #" << j << " is \"" << vec[j] << '"' << endl;
		}
	}
	return ALL_OK;
}
