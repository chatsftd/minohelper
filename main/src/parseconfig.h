#ifndef PARSECONFIG_H_90D37636D689F2E3EFDA47A380D42A820274F21C
#define PARSECONFIG_H_90D37636D689F2E3EFDA47A380D42A820274F21C
#include <string>
#include <iostream>

enum parsestat
{
	EMPTY_LINE,
	VALID_LINE,
	DELETION_LINE,
	INVALID_LINE
};

class config_value{
	int inside;

public:	
	friend std::ostream& operator<<(std::ostream& os, const config_value& val);
	friend std::istream& operator>>(std::istream& is, config_value& val);
	operator int() const{ return this->inside; }
};

parsestat parse_line(const std::string& str, std::string& varname, config_value& num);
bool is_varname(const std::string& str);

#endif/*PARSECONFIG_H_90D37636D689F2E3EFDA47A380D42A820274F21C*/
