#ifndef PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100
#define PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100
#include "status.h"
#include "point.h"
#include <iostream>
#include <vector>
#include <string>
enum Paren
{
	Parenthesis, 
	Bracket,
	Brace
};

struct meta
{
	Paren first;
	std::string second;
	point pos;
	meta(Paren pa, point po) : first(pa), second(""), pos(po) {}
	friend std::ostream& operator<<(std::ostream& o, const meta& p);
};
typedef std::vector<meta> SyntaxTree2; 

status parsemeta(SyntaxTree2& st, std::vector<std::string>& plane);
char paren_begin(Paren p);
char paren_end(Paren p);


#endif/*PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100*/
