#include "interpret.h"
#include "import.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void parse(vector<string>& vec,const string& a)
{
	stringstream input;
	input.str(a);
	string b; 
	while(input >> b)
	{
		vec.push_back(b);
	}
}

int interpret(const string& a)
{
	vector<string> vec;
	parse(vec,a);
	
	if(vec.empty()){return 0;}
#define eq(a) (vec[0] == string(a))	
	if(eq("exit"))
	{
		return -1;
	}
	else if(eq("import"))
	{
		return import_(vec);
	}
	
	int j=0;
	for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it,++j)
	{
		cout << "input #" << j << " is \"" << vec[j] << '"' << endl;
	}
	
	return 0;
}
