#include "state.h"

using namespace std;

state create_state(void)
{
	std::map<std::string,std::string> content;
	state stat;
	stat.content = content;
	return stat;
}
