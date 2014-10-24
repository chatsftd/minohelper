#ifndef STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#define STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ
#include <map>
#include <string>
#include <sstream>
#include <vector>

typedef std::vector<std::string> data;

struct state
{
	std::map<std::string,data> content;
};

state create_state(void);

data get_mino_data(std::stringstream& str);

#endif/*STATE_H_DEFINED_2014_10_13_BXAKBVZLZEASKXZAPKFYDFRHSFCBFQ*/
