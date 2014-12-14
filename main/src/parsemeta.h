#ifndef PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100
#define PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100
#include "status.h"
#include "state.h"
#include <vector>
#include <string>
#include "debug.h"
#include "constructmino.h"
#include <stack>
#include <utility>
enum Paren
{
	Parenthesis = ')', 
	Bracket     = ']',
	Brace       = '}'
};

typedef std::pair<Paren,std::string> meta;
typedef std::vector<meta> SyntaxTree2; 

status paren2(SyntaxTree2& st, std::vector<std::string>& plane);
char begin(Paren p);
char end(Paren p);


#endif/*PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100*/
