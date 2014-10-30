#include "parsemino.h"
#include "union.h"
#include <iostream>
#include <map>
using namespace std;
typedef pair<ID, char> atom;


static bool isSame(const vector< vector<atom> >& atom_plane, size_t i, size_t j, size_t i2, size_t j2)
{
	if(atom_plane.size() <= i  || atom_plane[i ].size() <= j ) return false;
	if(atom_plane.size() <= i2 || atom_plane[i2].size() <= j2) return false;
	char a = atom_plane[i ][j ].second;
	char b = atom_plane[i2][j2].second;
	if(a == ' ')return false;
	return a == b;
}

static void print_inside(const vector< vector<atom> >& atom_plane, size_t i, size_t j)
{
	cout << "(" << i+1 << ", " << j+1 << "): " << "(" << atom_plane[i][j].first << ",'" << atom_plane[i][j].second << "')" << flush;
}

typedef pair<size_t, size_t> point;
data parse_mino(const vector<string>& vec)
{
	vector< vector<atom> > atom_plane;
	map<ID, point> ItoP;
	ID id = 0;
	for(size_t i = 0, n = vec.size(); i < n; i++)
	{
		vector<atom> tmp;
		atom_plane.push_back(tmp);
		for(size_t j = 0, m = vec[i].size(); j < m; j++)
		{
			atom_plane[i].push_back(atom(id,vec[i][j]));
			ItoP[id] = point(i,j);
			id++;
		}
	}
	
	
	const ID id_max_plus_1 = id; // copy the value
	vector<ID> vec2;
	for(ID i = 0; i < id_max_plus_1; i++)
	{
		vec2.push_back(i);
	}
	
	UnionFind union_find = vec2;
	
	for(size_t i = 0, n = atom_plane.size(); i < n; i++)
	{
		for(size_t j = 0, m = atom_plane[i].size(); j < m; j++)
		{
			if(isSame(atom_plane,i,j,i,j-1))
			{
				print_inside(atom_plane,i,j); cout << " and ";
				print_inside(atom_plane,i,j-1); cout << " are the same." << endl;
				union_find.unite(atom_plane[i][j].first,atom_plane[i][j-1].first);
			}
			if(isSame(atom_plane,i,j,i-1,j))
			{
				print_inside(atom_plane,i,j); cout << " and ";
				print_inside(atom_plane,i-1,j); cout << " are the same." << endl;
				union_find.unite(atom_plane[i][j].first,atom_plane[i-1][j].first);
			}
		}
	}
	
	return vec; // fixme
}
