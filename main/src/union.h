#ifndef UNION_H_DEFINED_2014_10_15_049c46c6c5a6721a1fbf83a0b2a582514b3634c9
#define UNION_H_DEFINED_2014_10_15_049c46c6c5a6721a1fbf83a0b2a582514b3634c9
#include <vector>
typedef int ID;
typedef std::vector<ID> UnionFind;
ID root(const UnionFind& union_find, ID id);
void unite(UnionFind& union_find, const ID id1, const ID id2);

#endif/*UNION_H_DEFINED_2014_10_15_049c46c6c5a6721a1fbf83a0b2a582514b3634c9*/
