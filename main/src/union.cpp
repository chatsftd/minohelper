#include "union.h"
using namespace std;
ID UnionFind::root(ID id)
{
	ID parent_id;
	while(true)
	{
		parent_id = this->union_find[id];
		if(id == parent_id) return id;
		id = parent_id;
	}
}

void UnionFind::unite(const ID id1, const ID id2)
{
	ID root1 = this->root(id1);
	ID root2 = this->root(id2);
	this->union_find[root2] = root1;
}
