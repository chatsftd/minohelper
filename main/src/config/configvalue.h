#ifndef CONFIGVALUE_H_DEFINED_7C7EA0091CD1D3567A619F4DEE400AB70099BBC4
#define CONFIGVALUE_H_DEFINED_7C7EA0091CD1D3567A619F4DEE400AB70099BBC4
#include <string>
#include <iostream>

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



#endif/*CONFIGVALUE_H_DEFINED_7C7EA0091CD1D3567A619F4DEE400AB70099BBC4*/
