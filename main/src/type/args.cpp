#include "args.h"
#include "../lib/debug.h"
using namespace std;
string& arguments2::operator [](size_t n)
{
#ifndef NDEBUG 
	return this->inside.at(n);
#else
	return this->inside[n];
#endif
}

string arguments2::operator [](size_t n) const
{
	string str;
#ifndef NDEBUG 
	str = this->inside.at(n);
#else
	str = this->inside[n];
#endif
	return str;
}
