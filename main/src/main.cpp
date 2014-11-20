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
