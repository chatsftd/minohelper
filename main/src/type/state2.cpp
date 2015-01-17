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

bool color_palette::exist(char c) const
{
	return this->p.find(c) != this->p.end(); // checks whether it exist
}
