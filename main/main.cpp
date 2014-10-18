#include "interpret.h"
#include "import.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void init(vector<string>& vec, int argc, char** argv)
{
	vec.push_back(string("import"));
	for(int k = 1; k < argc; k++)
	{
		vec.push_back(string(argv[k]));
	}
}

int main(int argc, char** argv)
{
	if(argc >= 2)
	{
		vector<string> vec;
		init(vec,argc,argv);
		import_(vec);
	}
	
	while(true)
	{
		string a = "";
		cout << "> " << flush;
		getline(cin,a);
		int e = interpret(a);
		switch(e)
		{
			case -1: goto end; /* escape from while-true*/
			default: break; /* do nothing */
		}
	}
	
	end: return 0;
}
