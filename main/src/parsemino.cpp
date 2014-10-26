#include "parsemino.h"
#include <iostream>
using namespace std;

typedef int ID;


static bool isSame(const vector< vector< pair<ID, char> > >& something, size_t i, size_t j, size_t i2, size_t j2)
{
	if(something.size() <= i  || something[i ].size() <= j ) return false;
	if(something.size() <= i2 || something[i2].size() <= j2) return false;
	char a = something[i ][j ].second;
	char b = something[i2][j2].second;
	if(a == ' ')return false;
	return a == b;
}

static void print_inside(const vector< vector< pair<ID, char> > >& something, size_t i, size_t j)
{
	cout << "(" << i+1 << ", " << j+1 << "): " 
	 << "(" << something[i][j].first << ",'" << something[i][j].second << "')" << flush;
}

static ID root(const vector<ID>& union_find, ID id)
{
	ID parent_id;
	while(true)
	{
		parent_id = union_find[id];
		if(id == parent_id) return id;
		id = parent_id;
	}
}

static void unite(vector<ID>& union_find, const ID id1, const ID id2)
{
	ID root1 = root(union_find,id1);
	ID root2 = root(union_find,id2);
	union_find[root2] = root1;
}

data parse_mino(const vector<string>& vec)
{
	vector< vector< pair<ID, char> > > something;
	ID id = 0;
	for(size_t i = 0, n = vec.size(); i < n; i++)
	{
		vector< pair<ID, char> > tmp;
		something.push_back(tmp);
		for(size_t j = 0, m = vec[i].size(); j < m; j++)
		{
			pair<ID,char> pic(id,vec[i][j]); 
			id++;
			something[i].push_back(pic);
		}
	}
	
	
	const ID id_max_plus_1 = id; // copy the value
	vector<ID> union_find;
	
	for(ID i = 0; i < id_max_plus_1; i++)
	{
		union_find.push_back(i);
	}
	
	/*for(size_t i = 0, n = something.size(); i < n; i++)
	{
		for(size_t j = 0, m = something[i].size(); j < m; j++)
		{
			print_inside(something,i,j); cout << endl;
		}
	}*/
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
