#include "state.h"
#include "parsemino.h"
#include <iostream>
using namespace std;

state::state(void) : content() {}

data get_mino_data(stringstream& str)
{
	string s;
	vector<string> vec;
	while(getline(str,s))
	{
		vec.push_back(s);
	}
	return parse_mino(vec); 
}

