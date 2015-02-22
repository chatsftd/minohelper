#include "parseconfig.h"
#include <sstream>
using namespace std;


ostream& operator<<(ostream& os, const config_value& val)
{
  os << val.inside;
  return os;
}

istream& operator>>(istream& is, config_value& val)
{
  is >> val.inside;
  if(!is){ is.setstate(ios::failbit); }
  return is;
}

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
	if(init_char == '~')
	{
		pos++;
		goto parse_deletion_line; //located at the end of the function
	} 
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
	
	{ /* goto cannot jump over initialization */
		string leftover = str.substr(pos);
		stringstream ss(leftover.c_str());
		ss >> num;
		if(!ss){return INVALID_LINE;} 
	}
	return VALID_LINE;
	
	
	/************
	 * DELETION *
	 ************/
parse_deletion_line:
	while(true) // before varname
	{
		if(!isspace(str[pos])) break;
		pos++;
		if(pos >= str.size()){ return INVALID_LINE; } 
	}
	
	char init_char2 = str[pos];
	if(!is_varname_init_char(init_char2)){ return INVALID_LINE; } 
	varname += empty + init_char2;
	pos++;
	if(pos >= str.size()){ return DELETION_LINE; } 
	
	while(true)
	{
		char a = str[pos];
		if(!is_varname_more_char(str[pos])) break;
		pos++;
		varname += empty + a;
		if(pos >= str.size()) break;
	}
	return DELETION_LINE;
}
