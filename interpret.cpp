#include "interpret.h"
#include <iostream>
using namespace std;

int interpret(const string& a)
{
	if(a == string("exit"))
	{
		return -1;
	}
	cout << "input is \"" << a << '"' << endl;
	return 0;
}
