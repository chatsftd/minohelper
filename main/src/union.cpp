#include "union.h"
using namespace std;
ID root(const UnionFind& union_find, ID id)
{
	ID parent_id;
	while(true)
	{
		parent_id = union_find[id];
		if(id == parent_id) return id;
		id = parent_id;
	}
}

void unite(UnionFind& union_find, const ID id1, const ID id2)
{
	ID root1 = root(union_find,id1);
	ID root2 = root(union_find,id2);
	union_find[root2] = root1;
}
