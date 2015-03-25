#ifndef STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#define STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#include "mino.h"
#include "type/errorlevel.h"
#include "meta/state2.h"
#include "mjsn.h"
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
		file_data(const std::vector<mino>& m, const state2& st2) : minos(m), palette(st2.palette), labels(st2.labels), dir(st2.dir) {}
	};
	std::map<std::string, std::pair<mjsn,color_palette> > content;
	error_level error_status;
	state(void) : content(), error_status(ALL_OK) {}
};

typedef std::string file_path;
typedef std::map<file_path, std::pair<mjsn,color_palette> > file_map;


#endif/*STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ*/
