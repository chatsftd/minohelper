#include "header.h"
#include "interpret.h"
#include "import.h"
#include "state.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void init(vector<string>& vec, int argc, char** argv)
{
	vec.push_back("import");
	for(int k = 1; k < argc; k++)
	{
		vec.push_back(argv[k]);
	}
}

int main(int argc, char** argv)
{
	state st;
	if(argc >= 2)
	{
		vector<string> vec;
		init(vec,argc,argv);
		import_(st,vec);
	}
	
	while(true)
	{
		string tmp = "";
		cout << "> " << flush;
		getline(cin,tmp);
		switch(interpret(st,tmp))
		{
			case EXIT_ALL: goto end; /* escape from while-true */
			default: break; /* do nothing */
		}
	}
	
	end: return 0;
}
