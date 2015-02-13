#ifndef STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC
#define STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC
#include "../lib/maybe.h"
#include <map>
#include <string>
#include <iostream>

enum Color_
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

struct Color
{
	Color_ inside;
	Color(void) : inside(Null) {}
	Color(Color_ c) : inside(c) {}
	int to_int() const;
	std::string to_str() const;
	bool operator !() const;
	bool is_null() const;
	friend std::ostream& operator<<(std::ostream& o, const Color& p);
};




class color_palette
{
	std::map<char,Color> p;
	
public:
	Color default_color;
	color_palette(void) : p(), default_color(RED) {}
	bool exist(char c) const;
	Color get_color_of(char c) const;
	void set_color_of(char c, Color col);
};

struct state2
{
	color_palette palette;
};

#endif/*STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC*/
