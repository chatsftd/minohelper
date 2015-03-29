#include "parsemino.h"
#include "lib/union.h"
#include "mino.h"
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

Maybe<state::file_data> parse_mino(const state2& st2, const vector<string>& content)
{
	vector< vector<atom> > atom_plane;
	map<ID, point> ItoP;
	ID id = 0;
	for(size_t i = 0, n = content.size(); i < n; i++) {
		set<size_t> xs = st2.labels.last_x_positions();
		bool safe = !(xs.count(i)); // danger === directly after (direction ... )
		
		vector<atom> tmp;
		atom_plane.push_back(tmp);
		for(size_t j = 0, m = content[i].size(); j < m; j++) {
			if(!safe && content[i][j] != ' ') {
				cerr << "Minos cannot exist directly after meta info 'direction'" << endl; cout << endl;
				return Nothing<state::file_data>();
			}
			atom_plane[i].push_back(atom(id,content[i][j]));
			ItoP[id] = point(i,j);
			id++;
		}
	}
	
	
	const ID id_max_plus_1 = id; // copy the value
	vector<ID> vec2;
	for(ID i = 0; i < id_max_plus_1; i++) {
		vec2.push_back(i);
	}
	
	UnionFind union_find(vec2);
	
	for(size_t i = 0, n = atom_plane.size(); i < n; i++) {
		for(size_t j = 0, m = atom_plane[i].size(); j < m; j++) {
			if(j != 0 && isSame(atom_plane,i,j,i,j-1)) {
				union_find.unite(atom_plane[i][j].first,atom_plane[i][j-1].first);
			}
			if(i != 0 && isSame(atom_plane,i,j,i-1,j)) {
				union_find.unite(atom_plane[i][j].first,atom_plane[i-1][j].first);
			}
		}
	}
	
	
	typedef vector<ID> group;
	vector<group> groups = union_find.toGroups();
	
	vector<mino> groups2;
	for(size_t i = 0, n = groups.size(); i < n; i++) {
		vector<point> tmp;
		char c2; // the character used in the input
		for(size_t j = 0, m = groups[i].size(); j < m; j++) {
			/*
			x   :   p.first+1
			y   :   p.second+1
			id  :   groups[i][j]
			char:   atom_plane[p.first][p.second].second
			*/
			
			point p = ItoP[groups[i][j]];
			char c = atom_plane[p.first][p.second].second;
			if(c == ' ') continue; // ignore spaces
			c2 = c;
			tmp.push_back(p);
		}
		if(tmp.size() == 0) continue; // ignore spaces
		if(tmp.size() == 4) {
			groups2.push_back(mino(tmp,c2));
		} else {
			cerr << "Improper mino ";
			for(size_t k = 0; k < tmp.size(); k++) {
				cerr << tmp[k] << ',';
			}
			cerr << " which consists of " << tmp.size() << " pixel(s), not 4." << endl; cout << endl;
			return Nothing<state::file_data>();
		}
	}
	
	for(size_t i = 0, n = groups2.size(); i < n; i++) {
		cout << "mino #" << i+1 << ": " << groups2[i] << endl;
	}
	
	state::file_data dat(groups2, st2);
	return Just(dat);
}

