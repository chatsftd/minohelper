#ifndef POINT_H_DEFINED_CF36C208541539D3310C7C0CD820CAF8CA826EA2
#define POINT_H_DEFINED_CF36C208541539D3310C7C0CD820CAF8CA826EA2

#include <vector>
#include <iostream>

#define WRONG_PLACE (0xCCCCCCCC)
struct point
{
	size_t first;
	size_t second;
	point(size_t f, size_t s) : first(f), second(s) {}
	point() : first(WRONG_PLACE), second(WRONG_PLACE) {}
	friend std::ostream& operator<<(std::ostream& o, const point& p);
};

#endif/*POINT_H_DEFINED_CF36C208541539D3310C7C0CD820CAF8CA826EA2*/
