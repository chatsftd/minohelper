#ifndef META_H_DEFINED_6ED5F2CE1121311CCC9B3798F8F4CCB23219E5EF
#define META_H_DEFINED_6ED5F2CE1121311CCC9B3798F8F4CCB23219E5EF
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

char paren_begin(Paren p);
char paren_end(Paren p);

struct meta
{
	Paren paren;
	std::string content;
	point first_pos;
	meta(Paren pa, point po) : paren(pa), content(""), first_pos(po) {}
	std::vector<std::string> get_tokens() const;
	friend std::ostream& operator<<(std::ostream& o, const meta& p);
};




#endif/*META_H_DEFINED_6ED5F2CE1121311CCC9B3798F8F4CCB23219E5EF*/
