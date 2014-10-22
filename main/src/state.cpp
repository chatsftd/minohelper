#include "state.h"

using namespace std;

state create_state(void)
{
	state stat;
	std::map<std::string,data> content;
	stat.content = content;
	return stat;
}

data get_mino_data(const std::stringstream& str)
{
	return str.str(); // fixme
}
