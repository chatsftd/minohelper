#ifndef STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC
#define STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC
#include "../lib/maybe.h"
#include "../type/point.h"
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

enum direction
{
	TO_SOUTH,
	TO_EAST,
	TO_NORTH,
	TO_WEST
};

class dir_info
{
	std::map<point,direction> inside;
	
public:
	void set_direction(point p, direction dir){ this->inside[p] = dir; }
	void set_direction(size_t f, size_t s, direction dir){ this->inside[point(f,s)] = dir; }
	direction get_direction(point p) const;
	direction get_direction(size_t f, size_t s) const;
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

class label_info
{
	struct label_content
	{
		int num;
		point last_pos;
		direction dir;
		label_content(int n, point p, direction d) : num(n), last_pos(p), dir(d) {}
	};
	
	std::multimap<std::string,label_content> inside;
	
public:
	void set_label(const std::string& name, int num, point last_pos, direction dir); 
};

struct state2
{
	color_palette palette;
	dir_info dir;
	label_info labels;
};

#endif/*STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC*/
