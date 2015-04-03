#include "state2.h"
using namespace std;

string Color::to_str() const
{
	switch(this->color) {
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
	return static_cast<int>(this->color);
}

bool Color::operator !() const
{
	return this->color == Null;
}

bool Color::is_null() const
{
	return this->color == Null;
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
	if(this->exist(c)) {
		return this->p.find(c)->second;
	} else {
		return this->default_color;
	}
}

void label_info::set_label(const std::string& name, int num, point last_pos, direction dir)
{
	label_content content(num,last_pos,dir);
	multimap<string,label_content>::value_type key(name,content);
	this->label_map.insert(key);
}

set<size_t> label_info::last_x_positions() const
{
	set<size_t> xs;
	for(multimap<string,label_content>::const_iterator it = this->label_map.begin(); it != this->label_map.end(); ++it) {
		xs.insert(it->second.last_pos.first);
	}
	return xs;
}

multimap<string,label_info::label_content> label_info::get_labels_from_pos(point p) const
{
	multimap<string,label_info::label_content> mm;
	for(multimap<string,label_info::label_content>::const_iterator it = this->label_map.begin(); it != this->label_map.end(); ++it) {
		if(it->second.last_pos == p) { mm.insert(*it); }
	}
	return mm;
}
