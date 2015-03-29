#ifndef HEADER_H_DEFINED_2014_10_12_cikbjhewcbqxepjnjpeuiiszzqcse
#define HEADER_H_DEFINED_2014_10_12_cikbjhewcbqxepjnjpeuiiszzqcse
#include <string>
#include <iostream>
enum error_level_i /* DON'T FORGET TO MODIFY error_level::to_str() TOO */
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
	BEFORE_AFTER_DIRECTION,
	DIRECTION_MERGE_CONFLICT,
	DIRECTION_INCOMPLETE_MERGE,
	SOMETHING_WRONG = 0xCCCC
};

struct error_level {
	error_level_i inside;
	error_level(error_level_i s) : inside(s) {} /* no explicit */
	operator int() const;
	std::string to_str() const;
	friend std::ostream& operator<<(std::ostream& o, const error_level& s);
};

#endif/*HEADER_H_DEFINED_2014_10_12_cikbjhewcbqxepjnjpeuiiszzqcse*/
