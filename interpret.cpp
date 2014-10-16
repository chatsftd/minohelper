#include "interpret.h"
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
	typedef vector<string>::iterator VSI;
	vector<string> vec;
	
	parse(vec,a);
	
	if(vec.empty()){return 0;}
	
	if(vec[0] == string("exit")){return -1;}
	
	int j=0;
	for(VSI it = vec.begin(); it != vec.end(); ++it,++j)
	{
		cout << "input #" << j << " is \"" << vec[j] << '"' << endl;
	}
	
	return 0;
}
