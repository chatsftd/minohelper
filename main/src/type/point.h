#ifndef POINT_H_DEFINED_CF36C208541539D3310C7C0CD820CAF8CA826EA2
#define POINT_H_DEFINED_CF36C208541539D3310C7C0CD820CAF8CA826EA2
#include "../lib/debug.h"
#include <iostream>

#define WRONG_PLACE (0xCCCCCCCC)
struct point {
	size_t row;
	size_t column;
	point(size_t f, size_t s) : row(f), column(s) {}
	point() : row(WRONG_PLACE), column(WRONG_PLACE) {}
	friend std::ostream& operator<<(std::ostream& o, const point& p);
	
	point& operator-=(size_t x)
	{
		assert2("Negative index", this->row >= x);
		this->row -= x;
		return *this;
	}
	
	point& operator+=(size_t x)
	{
		this->row += x;
		return *this;
	}
};

inline point operator-(point lhs, size_t rhs) { lhs -= rhs; return lhs; }
inline point operator+(point lhs, size_t rhs) { lhs += rhs; return lhs; }
inline bool operator==(const point& lhs, const point& rhs) {return (lhs.row == rhs.row) && (lhs.column == rhs.column);}
inline bool operator!=(const point& lhs, const point& rhs) {return !operator==(lhs,rhs);}
inline bool operator< (const point& lhs, const point& rhs) {return (lhs.row+1 < rhs.row+1) ? true : (lhs.row+1 > rhs.row+1) ? false : (lhs.column+1 < rhs.column+1);}
inline bool operator> (const point& lhs, const point& rhs) {return  operator< (rhs,lhs);}
inline bool operator<=(const point& lhs, const point& rhs) {return !operator< (rhs,lhs);}
inline bool operator>=(const point& lhs, const point& rhs) {return !operator< (lhs,rhs);}

#endif/*POINT_H_DEFINED_CF36C208541539D3310C7C0CD820CAF8CA826EA2*/
