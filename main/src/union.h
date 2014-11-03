#ifndef UNION_H_DEFINED_2014_10_15_049c46c6c5a6721a1fbf83a0b2a582514b3634c9
#define UNION_H_DEFINED_2014_10_15_049c46c6c5a6721a1fbf83a0b2a582514b3634c9
#include <vector>
typedef int ID;

class UnionFind
{
private:
	std::vector<ID> parents;
	
public:
	UnionFind(const std::vector<ID>& uf) : parents(uf) {} 
	ID root(ID id);
	void unite(ID id1, ID id2);
	std::vector< std::vector<ID> > toGroups(void);
};



#endif/*UNION_H_DEFINED_2014_10_15_049c46c6c5a6721a1fbf83a0b2a582514b3634c9*/
