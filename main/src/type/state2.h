#ifndef STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC
#define STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC
#include "../lib/maybe.h"
#include <map>
#include <string>
enum Color
{
	RED = 0,
	ORANGE,
	YELLOW,
	GREEN,
	LIGHTBLUE,
	NAVY,
	PURPLE,
	WHITE,
	BLACK,
	HEAL,
	Null = 0xCCCC
};



std::string col_to_str(Color c);


struct color_palette
{
	std::map<char,Color> p;
	Color default_color;
	color_palette(void) : p(), default_color(Null) {}
};

struct state2
{
	color_palette palette;
};

#endif/*STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC*/
