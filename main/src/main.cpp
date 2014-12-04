#include "interpret.h"
#include "import.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
		status s = import_(st,vec);
		st.error_status = s;
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
