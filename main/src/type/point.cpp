#include "point.h"
#include "../lib/debug.h"
using namespace std;

ostream& operator<<(ostream& o, const point& p)
{
	assert2("Wrong point", p.row != WRONG_PLACE && p.column != WRONG_PLACE);
	return o << "(" << p.row+1 << "," << p.column+1 << ")";
}
