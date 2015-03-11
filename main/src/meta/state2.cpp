#include "state2.h"
using namespace std;

string Color::to_str() const
{
	switch(this->inside)
	{
		case RED: return "red";
		case ORANGE: return "orange";
		case YELLOW: return "yellow";
		case GREEN: return "green";
		case LIGHTBLUE: return "lightblue";
		case NAVY: return "navy";
		case PURPLE: return "purple";
		case BLACK: return "black";
		case WHITE: return "white";
		case HEAL: return "heal";
		default: return "Null";
	}
}

ostream& operator<<(ostream& o, const Color& p)
{
	return o << p.to_str();
}

int Color::to_int() const
{
	return static_cast<int>(this->inside);
}

bool Color::operator !() const
{
	return this->inside == Null;
}

bool Color::is_null() const
{
	return this->inside == Null;
}

bool color_palette::exist(char c) const
{
	if(this->p.find(c) == this->p.end()) return false;
	return !(this->p.find(c)->second.is_null());
}

void color_palette::set_color_of(char c, Color col)
{
	this->p[c] = col;
}

Color color_palette::get_color_of(char c) const
{
	if(this->exist(c))
	{
		return this->p.find(c)->second;
	}
	else
	{
		return this->default_color;
	}
}

direction dir_info::get_direction(point p) const
{
	direction ans = TO_SOUTH; //default
	for(map<point,direction>::const_iterator it = this->inside.begin(); it != this->inside.end(); ++it)
	{
		if(it->first > p) break;
		ans = it->second;
	}
	return ans;
}

direction dir_info::get_direction(size_t f, size_t s) const{return this->get_direction(point(f,s));}


void label_info::set_label(const std::string& name, int num, point last_pos, direction dir)
{
	label_content content(num,last_pos,dir);
	multimap<string,label_content>::value_type key(name,content);
	this->inside.insert(key);
}

set<point> label_info::last_positions() const
{
	set<point> ps;
	for(multimap<string,label_content>::const_iterator it = this->inside.begin(); it != this->inside.end(); ++it)
	{
		ps.insert(it->second.last_pos);
	}
	return ps;
}

set<size_t> label_info::last_x_positions() const
{
	set<size_t> xs;
	for(multimap<string,label_content>::const_iterator it = this->inside.begin(); it != this->inside.end(); ++it)
	{
		xs.insert(it->second.last_pos.first);
	}
	return xs;
}
