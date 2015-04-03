#include "args.h"
#include "../lib/debug.h"
#include <sstream>
using namespace std;
string& arguments2::operator [](size_t n)
{
#ifndef NDEBUG
	return this->tokens.at(n);
#else
	return this->tokens[n];
#endif
}

const string& arguments2::operator [](size_t n) const
{
	return
#ifndef NDEBUG
	    this->tokens.at(n)
#else
	    this->tokens[n]
#endif
	    ;
}

void arguments2::parse(const string& a)
{
	stringstream input;
	input.str(a);
	string b;
	while(input >> b) {
		this->push_back(b);
	}
}
