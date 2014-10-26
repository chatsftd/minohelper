#include "parsemino.h"
#include <iostream>
using namespace std;

typedef int ID;
data parse_mino(const vector<string>& vec)
{
	vector< vector< pair< ID, char> > > something;
	ID id = 0;
	for(size_t i = 0, n = vec.size(); i < n; i++)
	{
		vector< pair< ID, char> > tmp;
		something.push_back(tmp);
		for(size_t j = 0, m = vec[i].size(); j < m; j++)
		{
			pair< ID,char> pic(id,vec[i][j]); 
			id++;
			something[i].push_back(pic);
		}
	}
	
	for(size_t i = 0, n = something.size(); i < n; i++)
	{
		for(size_t j = 0, m = something[i].size(); j < m; j++)
		{
			cout << "(" << i+1 << ", " << j+1 << "): " 
				 << "(" << something[i][j].first << ",'" << something[i][j].second << "')" << endl;
			
		}
	}
	
	return vec; // fixme
}
