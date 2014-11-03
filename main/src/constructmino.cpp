#include "constructmino.h"
#include <cassert>

using namespace std;


mino::mino(const vector<point>& points) 
{
	assert(((void)"mino size is not 4", points.size() == 4)); // fixme
	this->p0 = points[0];
	this->p1 = points[1];
	this->p2 = points[2];
	this->p3 = points[3];
}

#ifndef NDEBUG
ostream& operator<<(ostream& o, const mino& m) 
{
	
    o      << "(" << m.p0.first+1 << "," << m.p0.second+1 << ")"
	<< "," << "(" << m.p1.first+1 << "," << m.p1.second+1 << ")"
	<< "," << "(" << m.p2.first+1 << "," << m.p2.second+1 << ")"
	<< "," << "(" << m.p3.first+1 << "," << m.p3.second+1 << ")"
	;
	return o;
}
#endif
