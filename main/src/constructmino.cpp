#include "constructmino.h"
#include <cassert>

using namespace std;


mino::mino(const vector<point>& points, char c) : ch(c) 
{
	assert(((void)"mino size is not 4", points.size() == 4)); // fixme
	this->p0 = points[0];
	this->p1 = points[1];
	this->p2 = points[2];
	this->p3 = points[3];
}

ostream& operator<<(ostream& o, const mino& m) 
{
	
    o      << "'" << m.ch << "' " 
	<< "(" << m.p0.first+1 << "," << m.p0.second+1 << ")"
	<< "," << "(" << m.p1.first+1 << "," << m.p1.second+1 << ")"
	<< "," << "(" << m.p2.first+1 << "," << m.p2.second+1 << ")"
	<< "," << "(" << m.p3.first+1 << "," << m.p3.second+1 << ")"
	
	;
	return o;
}
static inline size_t m(size_t a, size_t b){ return a < b ? a : b; }
static inline size_t min(size_t a, size_t b, size_t c, size_t d){ return m(m(a,b),m(c,d)); }

point mino::top_left() const
{
	return point(min(p0.first,p1.first,p2.first,p3.first),min(p0.second,p1.second,p2.second,p3.second));
}
