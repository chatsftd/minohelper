#include "errorlevel.h"
using namespace std;

string error_level::to_str() const
{
#define case_(a) case (a): return (string)(#a)
	switch(this->inside)
	{
		case_(EXIT_ALL);
		case_(ALL_OK);
		case_(INVALID_META);
		case_(IMPROPER_MINO);
		case_(INVALID_ARGS);
		case_(NO_FILES_LOADED);
		case_(NO_SUCH_COMMAND);
		case_(NO_SUCH_INDEX);
		case_(INVALID_FILEPATH);
		case_(CONFIG_WRITE_FAILED);
		case_(CONFIG_READ_FAILED);
		case_(CONFIG_FORMAT_WRONG);
		case_(CONFIG_VAR_NOT_FOUND);
		case_(BEFORE_AFTER_DIRECTION);
		default: return "SOMETHING_WRONG";
	}
}

ostream& operator<<(ostream& o, const error_level& s)
{
	return o << s.to_str();	
}

error_level::operator int() const
{
	return static_cast<int>(this->inside);
}
