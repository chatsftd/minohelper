#ifndef PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100
#define PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100
#include "../type/errorlevel.h"
#include "../type/point.h"
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
	Paren paren;
	std::string content;
	point pos;
	meta(Paren pa, point po) : paren(pa), content(""), pos(po) {}
	std::vector<std::string> get_tokens() const;
	friend std::ostream& operator<<(std::ostream& o, const meta& p);
};
typedef std::vector<meta> all_meta;

error_level parsemeta(all_meta& st, std::vector<std::string>& plane);



#endif/*PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100*/
