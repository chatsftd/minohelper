#ifndef PARSECONFIG_H_90D37636D689F2E3EFDA47A380D42A820274F21C
#define PARSECONFIG_H_90D37636D689F2E3EFDA47A380D42A820274F21C

#include <string>

enum parsestat
{
	EMPTY_LINE,
	VALID_LINE,
	INVALID_LINE
};

typedef int config_value;

parsestat parse_line(const std::string& str, std::string& varname, config_value& num);
bool is_varname(const std::string& str);

#endif/*PARSECONFIG_H_90D37636D689F2E3EFDA47A380D42A820274F21C*/
