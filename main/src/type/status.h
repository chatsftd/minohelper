#ifndef HEADER_H_DEFINED_2014_10_12_cikbjhewcbqxepjnjpeuiiszzqcse
#define HEADER_H_DEFINED_2014_10_12_cikbjhewcbqxepjnjpeuiiszzqcse
#include <string>
#include <iostream>
enum status_i /* DON'T FORGET TO MODIFY status::to_str() TOO */
{
	EXIT_ALL = -1,
	ALL_OK = 0,
	INVALID_META,
	IMPROPER_MINO,
	INVALID_ARGS,
	NO_FILES_LOADED,
	NO_SUCH_COMMAND,
	NO_SUCH_INDEX,
	INVALID_FILEPATH,
	CONFIG_WRITE_FAILED,
	CONFIG_READ_FAILED,
	CONFIG_FORMAT_WRONG,
	CONFIG_VAR_NOT_FOUND,
	SOMETHING_WRONG = 0xCCCC
};

struct status
{
	status_i inside;
	status(status_i s) : inside(s) {} /* no explicit */
	operator int() const;
	std::string to_str() const;
	friend std::ostream& operator<<(std::ostream& o, const status& s);
};



#endif/*HEADER_H_DEFINED_2014_10_12_cikbjhewcbqxepjnjpeuiiszzqcse*/
