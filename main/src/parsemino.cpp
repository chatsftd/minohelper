#include "parsemino.h"
#include <iostream>
using namespace std;

data parse_mino(const vector<string>& vec)
{
	for(size_t i = 0, n = vec.size(); i < n; i++)
	{
		for(size_t j = 0, m = vec[i].size(); j < m; j++)
		{
			cout << "(" << i+1 << ", " << j+1 << "): " << vec[i][j] << endl;
		}
	}
	return vec; // fixme
}
