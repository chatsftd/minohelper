#ifndef STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#define STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#include "mino.h"
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
		label_info labels;
		dir_info dir;
		file_data(void) : minos(), palette() {}
		file_data(const std::vector<mino>& m, color_palette pal, label_info lab, dir_info d) : minos(m), palette(pal), labels(lab), dir(d) {}
	};
	std::map<std::string,state::file_data> content;
	error_level error_status;
	state(void) : content(), error_status(ALL_OK) {}
};

typedef std::string file_path;
typedef std::map<file_path,state::file_data> file_map;


#endif/*STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ*/
