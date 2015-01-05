#include "interpret.h"
#include "import.h"
#include "export.h"
#include "parsearg.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void init(state& st, const vector<string>& v)
{
	string input, output;
	status s2 = parse_arg(input,output,v);
	if(s2 != ALL_OK){ st.error_status = s2;	return; }
	if(input == ""){ st.error_status = ALL_OK; return; }
	
	vector<string> vec;
	vec.push_back("import");
	vec.push_back(input);
	status s = import_(st,vec);
	st.error_status = s;
	
	if(output == "") return;
	
	
	vector<string> vec2;
	vec2.push_back("export");
	vec2.push_back(input);
	vec2.push_back("-o");
	vec2.push_back(output);
	
	status s3 = export_(st,vec2); //fixme: ignored
	exit(0); //fixme
}

int main(int argc, char** argv)
{
	state st;
	if(argc >= 2)
	{
		vector<string> vec;
		vec.push_back("import");
		for(int k = 1; k < argc; k++)
		{
			vec.push_back(argv[k]);
		}
		init(st,vec);
	}
	
	while(true)
	{
		string tmp = "";
		cout << "> " << flush;
		getline(cin,tmp);
		status s = interpret(st,tmp);
		st.error_status = s;
		switch(s)
		{
			case EXIT_ALL: goto end; /* escape from while-true */
			default: break; /* do nothing */
		}
	}
	
	end: return 0;
}
