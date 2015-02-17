#include "parseconfig.h"
#include <sstream>
using namespace std;

static inline bool is_varname_init_char(char a){ return isalpha(a) || (a == '_'); }
static inline bool is_varname_more_char(char a){ return isalnum(a) || (a == '_') || (a == '.'); }

bool is_varname(const string& str)
{
	if(str.empty() || !is_varname_init_char(str[0])){ return false; }
	for(size_t i = 1; i < str.size(); i++)
	{
		if(!is_varname_more_char(str[i])){ return false; }
	}
	return true;
}

parsestat parse_line(const string& str, string& varname, config_value& num)
{
	size_t pos = 0;
	varname = "";
	const static string empty = "";
	if(str.size() == 0){ return EMPTY_LINE; }
	
	while(true) // before varname
	{
		if(!isspace(str[pos])) break;
		pos++;
		if(pos >= str.size()){ return EMPTY_LINE; } 
	}
	
	char init_char = str[pos];
	if(!is_varname_init_char(init_char)){ return INVALID_LINE; } 
	varname += empty + init_char;
	pos++;
	if(pos >= str.size()){ return INVALID_LINE; } 
	
	while(true)
	{
		char a = str[pos];
		if(!is_varname_more_char(str[pos])) break;
		pos++;
		varname += empty + a;
		if(pos >= str.size()){ return INVALID_LINE; } 
	}
	
	while(true) // after varname
	{
		if(!isspace(str[pos])) break;
		pos++;
		if(pos >= str.size()){ return INVALID_LINE; } 
	}
	
	if(str[pos++] != '='){ return INVALID_LINE; } 
	if(pos >= str.size()){ return INVALID_LINE; } 
	
	string leftover = str.substr(pos);
	stringstream ss(leftover.c_str());
	ss >> num;
	if(!ss){return INVALID_LINE;} 
	return VALID_LINE;
}
