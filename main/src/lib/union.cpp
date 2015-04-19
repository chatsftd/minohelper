#include "union.h"
#include <map>
#include <stack>
using namespace std;
ID UnionFind::root(ID id)
{
	if(this->parents[id] == id) {
		return id;
	} else {
		return this->parents[id] = this->root(this->parents[id]);
	}
}

void UnionFind::unite(ID id1, ID id2)
{
	ID root1 = this->root(id1);
	ID root2 = this->root(id2);
	if(root1 == root2) return;
	
	if(this->rank[id1] < this->rank[id2]) {
		this->parents[root1] = root2;
	} else {
		this->parents[root2] = root1;
		if(this->rank[id1] == this->rank[id2]) this->rank[id1]++;
	}
}

vector< vector<ID> > UnionFind::toGroups(void)
{
	typedef vector<ID> group;
	map<ID, group> buf; // map from `root ID` to `group`
	
	size_t size = this->parents.size();
	
	for(size_t i = 0; i < size; i++) {
		ID i2 = i;
		buf[this->root(i2)].push_back(i2);
	}
	
	vector<group> result;
	for(const auto& pa : buf) {
		result.push_back(pa.second);
	}
	return result;
}

