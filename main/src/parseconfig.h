#ifndef PARSECONFIG_H_90D37636D689F2E3EFDA47A380D42A820274F21C
#define PARSECONFIG_H_90D37636D689F2E3EFDA47A380D42A820274F21C
#include <string>
#include <iostream>

enum parsestat {
	EMPTY_LINE,
	VALID_LINE,
	DELETION_LINE,
	INVALID_LINE
};

enum config_value_type {
	CONFIG_INT_TYPE,
	CONFIG_BOOL_TYPE,
	CONFIG_STRING_TYPE
};

class config_value
{
	config_value_type type;
	struct { /*union*/
		int int_value;
		bool bool_value;
		std::string string_value;
	} u;
	
public:
	friend std::ostream& operator<<(std::ostream& os, const config_value& val);
	friend std::istream& operator>>(std::istream& is, config_value& val);
};

parsestat parse_line(const std::string& str, std::string& varname, config_value& num);
bool is_varname(const std::string& str);

#endif/*PARSECONFIG_H_90D37636D689F2E3EFDA47A380D42A820274F21C*/
