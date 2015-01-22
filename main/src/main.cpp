#include "interpret.h"
#include "import.h"
#include "export.h"
#include "parsearg.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static status init(int& ret, state& st, const arguments2& args)
{
	string input, output;
	ret = 0;
	status s2 = parse_arg(input,output,args);
	if(s2 != ALL_OK){ return s2; }
	if(input == ""){ return ALL_OK; }
	
	arguments2 args2;
	args2.push_back("import");
	args2.push_back(input);
	status s = import_(st,args2);
	
	if(output == ""){ return s; }
	
	arguments2 args3;
	args3.push_back("export");
	args3.push_back(input);
	args3.push_back("-o");
	args3.push_back(output);
	
	status s3 = export_(st,args3); 
	ret = s3;
	return EXIT_ALL;
}

int main(int argc, char** argv)
{
	state st;
	int ret = 0;
	if(argc >= 2)
	{
		arguments2 args;
		args.push_back("import");
		for(int k = 1; k < argc; k++)
		{
			args.push_back(argv[k]);
		}
		status s6 = init(ret,st,args);
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
