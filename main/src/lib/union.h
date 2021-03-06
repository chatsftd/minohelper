#ifndef UNION_H_DEFINED_2014_10_15_049c46c6c5a6721a1fbf83a0b2a582514b3634c9
#define UNION_H_DEFINED_2014_10_15_049c46c6c5a6721a1fbf83a0b2a582514b3634c9
#include <vector>
typedef int ID;

class UnionFind
{
private:
	std::vector<ID> parents;
	std::vector<std::size_t> rank;
	
public:
	explicit UnionFind(const std::vector<ID>& id_list) : parents(id_list), rank(id_list.size(),0) {}
	ID root(ID id);
	void unite(ID id1, ID id2);
	std::vector< std::vector<ID> > toGroups(void);
};



#endif/*UNION_H_DEFINED_2014_10_15_049c46c6c5a6721a1fbf83a0b2a582514b3634c9*/
