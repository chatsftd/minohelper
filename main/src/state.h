#ifndef STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#define STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#include "constructmino.h"
#include <map>
#include <string>
#include <sstream>
#include <vector>
class data
{
public:
	std::vector<mino> minos;
	data(void);
	data(const std::vector<mino>& minos_);
};


class state
{
public:
	std::map<std::string,data> content;
	state(void);
};




#endif/*STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ*/