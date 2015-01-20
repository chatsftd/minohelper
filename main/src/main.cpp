#include "interpret.h"
#include "import.h"
#include "export.h"
#include "parsearg.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static status init(int& ret, state& st, const arguments& v)
{
	string input, output;
	ret = 0;
	status s2 = parse_arg(input,output,v);
	if(s2 != ALL_OK){ return s2; }
	if(input == ""){ return ALL_OK; }
	
	arguments vec;
	vec.push_back("import");
	vec.push_back(input);
	status s = import_(st,vec);
	
	if(output == ""){ return s; }
	
	arguments vec2;
	vec2.push_back("export");
	vec2.push_back(input);
	vec2.push_back("-o");
	vec2.push_back(output);
	
	status s3 = export_(st,vec2); 
	ret = s3;
	return EXIT_ALL;
}

int main(int argc, char** argv)
{
	state st;
	int ret = 0;
	if(argc >= 2)
	{
		arguments vec;
		vec.push_back("import");
		for(int k = 1; k < argc; k++)
		{
			vec.push_back(argv[k]);
		}
		status s6 = init(ret,st,vec);
		st.error_status = s6;
		switch(s6)
		{
			case EXIT_ALL: goto end; 
			default: break; /* do nothing */
		}
	}
	
	while(true)
	{
		string tmp = "";
		cout << "> " << flush;
		getline(cin,tmp);
		status s = interpret(st,tmp);
		switch(s)
		{
			case EXIT_ALL:
				ret = st.error_status;
				goto end; /* escape from while-true */
			default: break; /* do nothing */
		}
		st.error_status = s;
	}
	
	end: return ret;
}
