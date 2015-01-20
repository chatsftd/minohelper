#include "args.h"
#include "../lib/debug.h"
#include <sstream>
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

void arguments2::parse(const string& a)
{
	stringstream input;
	input.str(a);
	string b;
	while(input >> b)
	{
		this->push_back(b);
	}
}
