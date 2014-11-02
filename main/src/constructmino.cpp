#include "constructmino.h"
#include <cassert>

using namespace std;


mino::mino(vector<point> points) 
{
	assert(((void)"mino size is not 4", points.size() == 4)); // fixme
	this->p0 = points[0];
	this->p1 = points[1];
	this->p2 = points[2];
	this->p3 = points[3];
}

#ifndef NDEBUG
ostream& operator<<(ostream& o, mino m) 
{
	
    o      << "(" << m.p0.first << "," << m.p0.second << ")"
	<< "," << "(" << m.p1.first << "," << m.p1.second << ")"
	<< "," << "(" << m.p2.first << "," << m.p2.second << ")"
	<< "," << "(" << m.p3.first << "," << m.p3.second << ")"
	;
	return o;
}
#endif
