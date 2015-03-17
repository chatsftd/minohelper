#ifndef POINT_H_DEFINED_CF36C208541539D3310C7C0CD820CAF8CA826EA2
#define POINT_H_DEFINED_CF36C208541539D3310C7C0CD820CAF8CA826EA2
#include "../lib/debug.h"
#include <iostream>

#define WRONG_PLACE (0xCCCCCCCC)
struct point
{
	size_t first;
	size_t second;
	point(size_t f, size_t s) : first(f), second(s) {}
	point() : first(WRONG_PLACE), second(WRONG_PLACE) {}
	friend std::ostream& operator<<(std::ostream& o, const point& p);
	
	point& operator-=(size_t x) 
	{ 
		assert2("Negative index", this->first >= x);
		this->first -= x;
		return *this; 
	}
};

inline point operator-(point lhs, size_t rhs) { lhs -= rhs; return lhs; }
inline bool operator==(const point& lhs, const point& rhs){return (lhs.first == rhs.first) && (lhs.second == rhs.second);}
inline bool operator!=(const point& lhs, const point& rhs){return !operator==(lhs,rhs);}
inline bool operator< (const point& lhs, const point& rhs){return (lhs.first < rhs.first) ? true : (lhs.first > rhs.first) ? false : (lhs.second < rhs.second);}
inline bool operator> (const point& lhs, const point& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const point& lhs, const point& rhs){return !operator< (rhs,lhs);}
inline bool operator>=(const point& lhs, const point& rhs){return !operator< (lhs,rhs);}

#endif/*POINT_H_DEFINED_CF36C208541539D3310C7C0CD820CAF8CA826EA2*/
