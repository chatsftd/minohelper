#include "interpret.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	string a = "";
	while(true)
	{
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
