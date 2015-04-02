#ifndef STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC
#define STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC
#include "../lib/maybe.h"
#include "../type/point.h"
#include <map>
#include <string>
#include <iostream>
#include <set>

enum Color_ {
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

class Color
{
	Color_ color;
	
public:
	Color(void) : color(Null) {}
	Color(Color_ c) : color(c) {}
	int to_int() const;
	std::string to_str() const;
	bool operator !() const;
	bool is_null() const;
	friend std::ostream& operator<<(std::ostream& o, const Color& p);
};

enum direction {
	TO_SOUTH,
	TO_EAST,
	TO_NORTH,
	TO_WEST
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
public:
	struct label_content {
		int num;
		point last_pos;
		direction dir;
		label_content(int n, point p, direction d) : num(n), last_pos(p), dir(d) {}
	};
	
private:
	std::multimap<std::string,label_content> label_map;
	
public:
	void set_label(const std::string& name, int num, point last_pos, direction dir);
	std::set<size_t> last_x_positions() const;
	std::multimap<std::string,label_content> get_labels_from_pos(point p) const;
};

struct state2 {
	class dir_info
	{
		std::map<point,direction> all_points;
		std::map<point,point> from_first_to_last;
		
	public:
		void set_direction(point p, direction dir) { this->all_points[p] = dir; }
		void set_direction(size_t f, size_t s, direction dir) { this->all_points[point(f,s)] = dir; }
		void set_transform(point p, point p2) { this->from_first_to_last[p] = p2; }
		std::map<point,direction> get_all_points() const { return this->all_points; }
		std::map<point,point> get_transform() const { return this->from_first_to_last; }
	};
	
	color_palette palette;
	dir_info dir;
	label_info labels;
};

#endif/*STATE2_H_DEFINED_1373E8A8C125AF49724367EE8ADFD116500B73AC*/
