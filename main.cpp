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
		if(e) break;
	}
	return 0;
}
