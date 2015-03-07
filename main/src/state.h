#ifndef STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#define STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#include "constructmino.h"
#include "type/errorlevel.h"
#include "meta/state2.h"
#include <map>
#include <string>
#include <vector>


class state
{
public:
	class file_data
	{
	public:
		std::vector<mino> minos;
		color_palette palette;
		file_data(void) : minos(), palette() {}
		file_data(const std::vector<mino>& m, color_palette pal) : minos(m), palette(pal) {}
	};
	std::map<std::string,state::file_data> content;
	error_level error_status;
	state(void) : content(), error_status(ALL_OK) {}
};




#endif/*STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ*/
