#include "status.h"
using namespace std;

string status::to_str() const
{
#define case_(a) case (a): return (string)(#a)
	switch(this->inside)
	{
		case_(EXIT_ALL);
		case_(INVALID_META);
		case_(IMPROPER_MINO);
		case_(INVALID_ARGS);
		case_(NO_FILES_LOADED);
		case_(NO_SUCH_COMMAND);
		case_(NO_SUCH_INDEX);
		case_(INVALID_FILEPATH);
		case_(CONFIG_WRITE_FAILED);
		case_(CONFIG_READ_FAILED);
		case_(CONFIG_VAR_NOT_FOUND);
		case_(CONFIG_FORMAT_WRONG);
		case_(SOMETHING_WRONG);
		default: return "ALL_OK";
	}
}

ostream& operator<<(ostream& o, const status& s)
{
	return o << s.to_str();	
}

status::operator int() const
{
	return static_cast<int>(this->inside);
}
