#ifndef STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#define STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#include "constructmino.h"
#include "type/errorlevel.h"
#include "type/state2.h"
#include <map>
#include <string>
#include <vector>
class data
{
public:
	std::vector<mino> minos;
	color_palette palette;
	data(void);
	data(const std::vector<mino>& minos_, color_palette pal);
};


class state
{
public:
	std::map<std::string,data> content;
	error_level error_status;
	state(void);
};




#endif/*STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ*/
