#include "parsemino.h"
#include "union.h"
#include <iostream>
using namespace std;
typedef pair<ID, char> atom;


static bool isSame(const vector< vector<atom> >& something, size_t i, size_t j, size_t i2, size_t j2)
{
	if(something.size() <= i  || something[i ].size() <= j ) return false;
	if(something.size() <= i2 || something[i2].size() <= j2) return false;
	char a = something[i ][j ].second;
	char b = something[i2][j2].second;
	if(a == ' ')return false;
	return a == b;
}

static void print_inside(const vector< vector<atom> >& something, size_t i, size_t j)
{
	cout << "(" << i+1 << ", " << j+1 << "): " << "(" << something[i][j].first << ",'" << something[i][j].second << "')" << flush;
}

data parse_mino(const vector<string>& vec)
{
	vector< vector<atom> > something;
	ID id = 0;
	for(size_t i = 0, n = vec.size(); i < n; i++)
	{
		vector<atom> tmp;
		something.push_back(tmp);
		for(size_t j = 0, m = vec[i].size(); j < m; j++)
		{
			something[i].push_back(atom(id,vec[i][j]));
			id++;
		}
	}
	
	
	const ID id_max_plus_1 = id; // copy the value
	UnionFind union_find;
	
	for(ID i = 0; i < id_max_plus_1; i++)
	{
		union_find.push_back(i);
	}
	
	for(size_t i = 0, n = something.size(); i < n; i++)
	{
		for(size_t j = 0, m = something[i].size(); j < m; j++)
		{
			if(isSame(something,i,j,i,j-1))
			{
				print_inside(something,i,j); cout << " and ";
				print_inside(something,i,j-1); cout << " are the same." << endl;
				unite(union_find,something[i][j].first,something[i][j-1].first);
			}
			if(isSame(something,i,j,i-1,j))
			{
				print_inside(something,i,j); cout << " and ";
				print_inside(something,i-1,j); cout << " are the same." << endl;
				unite(union_find,something[i][j].first,something[i-1][j].first);
			}
			
			
			
		}
	}
	
	return vec; // fixme
}
