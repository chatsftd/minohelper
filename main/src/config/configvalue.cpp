#include "configvalue.h"
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
	case CONFIG_STRING_TYPE: os << quote(val.u.string_value); break;
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
	is.clear();
	
	read_quoted_string(is, val.u.string_value);
	if(is) {
		val.type = CONFIG_STRING_TYPE;
		return is;
	}
	is.clear();
	
	
	is.setstate(ios::failbit);
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

