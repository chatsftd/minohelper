#ifndef CONSTRUCT_MINO_H_DEFINED_28957c66eaef03980eb60b8ffdf0b85d11ca0744
#define CONSTRUCT_MINO_H_DEFINED_28957c66eaef03980eb60b8ffdf0b85d11ca0744 
#include <vector>
#include <iostream>
typedef std::pair<size_t, size_t> point;

class mino
{
public:
	point p0;
	point p1;
	point p2;
	point p3;
	char ch;
	mino(const std::vector<point>& points, char c);
	
	friend std::ostream& operator<<(std::ostream& o, const mino& m);
	
	point top_left() const;

}; // fixme




#endif/*CONSTRUCT_MINO_H_DEFINED_28957c66eaef03980eb60b8ffdf0b85d11ca0744*/
