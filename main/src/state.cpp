#include "state.h"
#include <iostream>
using namespace std;
static data parse_data(const vector<string>& vec);

state create_state(void)
{
	state stat;
	std::map<std::string,data> content;
	stat.content = content;
	return stat;
}

data get_mino_data(stringstream& str)
{
	string s;
	vector<string> vec;
	while(getline(str,s))
	{
		vec.push_back(s);
	}
	return parse_data(vec); 
}

static data parse_data(const vector<string>& vec)
{
	for(size_t i=0,n=vec.size();i<n;i++)
	{
		for(size_t j=0,m=vec[i].size();j<m;j++)
		{
			cout << "(" << i+1 << ", " << j+1 << "): " << vec[i][j] << endl;
		}
	}
	return vec; // fixme
}
