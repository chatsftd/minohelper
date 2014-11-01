#include "constructmino.h"
#include <cassert>
using namespace std;


mino::mino(vector<point> points) :
 p0(((void)(points.size() == 4), points[0])) ,
 p1(points[1]) ,
 p2(points[2]) ,
 p3(points[3])
{
	
}
