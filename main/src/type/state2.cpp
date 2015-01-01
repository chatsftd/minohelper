#include "state2.h"
using namespace std;

string col_to_str(Color c)
{
	switch(c)
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
		default: return "heal";
	}
}
