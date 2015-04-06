#include "parseconfig.h"
#include <cstring>
#include <sstream>
using namespace std;

static istream& read_quoted_string(istream& is, string& res);
static string quote(const string& str)
{
	string res = "\"";
	for(size_t i = 0; i < str.size(); i++) {
		switch(str[i]) {
		case '\a': res += "\\a"; break;
		case '\b': res += "\\b"; break;
		case '\f': res += "\\f"; break;
		case '\n': res += "\\n"; break;
		case '\r': res += "\\r"; break;
		case '\t': res += "\\t"; break;
		case '\v': res += "\\v"; break;
		case '\"': res += "\\\""; break;
		case '\\': res += "\\\\"; break;
		default: res.append(1,str[i]); break;
		}
	}
	res += "\"";
	return res;
}

ostream& operator<<(ostream& os, const config_value& val)
{
	switch(val.type) {
	case CONFIG_INT_TYPE: os << val.u.int_value; break;
	case CONFIG_BOOL_TYPE: {
		ios::fmtflags flags = os.flags();
		os << boolalpha << val.u.bool_value;
		os.flags(flags);
		break;
	}
	}
	
	return os;
}

istream& operator>>(istream& is, config_value& val)
{
	is >> val.u.int_value;
	if(is) {
		val.type = CONFIG_INT_TYPE;
		return is;
	}
	is.clear();
	
	
	ios::fmtflags flags = is.flags();
	is >> boolalpha >> val.u.bool_value;
	is.flags(flags);
	if(is) {
		val.type = CONFIG_BOOL_TYPE;
		return is;
	}
	
	is.setstate(ios::failbit);
	return is;
}

static inline bool is_varname_init_char(char a) { return strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz"           ,a) != NULL; }
static inline bool is_varname_more_char(char a) { return strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz.0123456789",a) != NULL; }

istream& read_variable(istream& is, string& name)
{
	name = "";
	is >> ws; // remove whitespace
	if(!is_varname_init_char(is.peek())) {
		is.setstate(ios::failbit);
		return is;
	}
	
	name.append(1,is.get());
	
	while(!is.eof()) {
		char c2 = is.peek();
		if(is_varname_more_char(c2)) {
			name.append(1,is.get());
		} else { break; }
	}
	
	return is;
}

static istream& read_quoted_string(istream& is, string& res)
{
	res = "";
	is >> ws;
	char q = is.peek();
	if(q != '"' && q != '\'') { goto failure; }
	is.get();
	
	while(!is.eof()) {
		char c = is.get();
		if(c == q) { return is; }
		if(c != '\\') {
			res.append(1,c);
			continue;
		}
		
		if(is.eof()) goto failure;
		char c2 = is.get();
		switch(c2) {
		case 'a': res += "\a"; break;
		case 'b': res += "\b"; break;
		case 'f': res += "\f"; break;
		case 'n': res += "\n"; break;
		case 'r': res += "\r"; break;
		case 't': res += "\t"; break;
		case 'v': res += "\v"; break;
		case '"': res += "\""; break;
		case '\'': res += "'"; break;
		case '\\': res += "\\"; break;
		default: goto failure;
		}
	}
	goto failure;
	
failure:
	is.setstate(ios::failbit);
	return is;
}

bool is_varname(const string& str)
{
	if(str.empty() || !is_varname_init_char(str[0])) { return false; }
	for(size_t i = 1; i < str.size(); i++) {
		if(!is_varname_more_char(str[i])) { return false; }
	}
	return true;
}

parsestat parse_line(const string& str, string& varname, config_value& num)
{
	if(str.empty()) { return EMPTY_LINE; }
	
	stringstream ss(str.c_str());
	ss >> ws;
	if(ss.eof()) { return EMPTY_LINE; }
	
	
	if(ss.peek() == '~') {
		ss.get();
		read_variable(ss,varname);
		if(!ss) { return INVALID_LINE; }
		
		ss >> ws;
		if(!ss.eof()) { return INVALID_LINE; }
		return DELETION_LINE;
	} else {
		read_variable(ss,varname);
		ss >> ws;
		if(ss.peek() != '=') { return INVALID_LINE; }
		else {
			ss.get();
			ss >> num;
			if(!ss) {return INVALID_LINE;}
			
			ss >> ws;
			if(!ss.eof()) { return INVALID_LINE; }
			return VALID_LINE;
		}
	}
}
