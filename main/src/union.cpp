#include "union.h"
#include <map>
using namespace std;
ID UnionFind::root(ID id)
{
	ID parent_id;
	while(true)
	{
		parent_id = this->parents[id];
		if(id == parent_id) return id;
		id = parent_id;
	}
}

void UnionFind::unite(const ID id1, const ID id2)
{
	ID root1 = this->root(id1);
	ID root2 = this->root(id2);
	this->parents[root2] = root1;
}

vector< vector<ID> > UnionFind::toGroups(void)
{
	typedef vector<ID> group; 
	map<ID, group> buf; // map from `root ID` to `group`
	
	size_t size = this->parents.size();
	
	for(size_t i = 0; i < size; i++) 
	{
		ID i2 = i;
		buf[this->root(i2)].push_back(i2);
	}
	
	vector<group> result;
	for(map<ID, group>::iterator it = buf.begin(); it != buf.end(); ++it)
    {
        result.push_back(it->second);
    }
	return result;
}

