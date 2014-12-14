#include "point.h"
#include "debug.h"
using namespace std;

ostream& operator<<(ostream& o, const point& p)
{
	assert2("Wrong point", p.first != WRONG_PLACE && p.second != WRONG_PLACE);
	return o << "(" << p.first+1 << "," << p.second+1 << ")";	
}
