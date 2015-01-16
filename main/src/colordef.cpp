#include "colordef.h"
#include "lib/maybe.h"
#include <iostream>
using namespace std;

static Maybe<Color> get_color(const string& str)
{
#define if2(a) if(str == static_cast<string>(a))
	if2("r") return Just(RED);
	if2("o") return Just(ORANGE);
	if2("y") return Just(YELLOW);
	if2("g") return Just(GREEN);
	if2("l") return Just(LIGHTBLUE);
	if2("n") return Just(NAVY);
	if2("p") return Just(PURPLE);
	if2("b") return Just(BLACK);
	if2("w") return Just(WHITE);
	if2("h") return Just(HEAL);
	if2("red") return Just(RED);
	if2("ora") return Just(ORANGE);
	if2("yel") return Just(YELLOW);
	if2("gre") return Just(GREEN);
	if2("lig") return Just(LIGHTBLUE);
	if2("nav") return Just(NAVY);
	if2("blu") return Just(NAVY);
	if2("pur") return Just(PURPLE);
	if2("vio") return Just(PURPLE);
	if2("bla") return Just(BLACK);
	if2("whi") return Just(WHITE);
	if2("hea") return Just(HEAL);
	if2("pin") return Just(HEAL);
	if2("orange") return Just(ORANGE);
	if2("yellow") return Just(YELLOW);
	if2("green") return Just(GREEN);
	if2("lightblue") return Just(LIGHTBLUE);
	if2("navy") return Just(NAVY);
	if2("blue") return Just(NAVY);
	if2("purple") return Just(PURPLE);
	if2("violet") return Just(PURPLE);
	if2("black") return Just(BLACK);
	if2("white") return Just(WHITE);
	if2("heal") return Just(HEAL);
	if2("pink") return Just(HEAL);
	else return Nothing<Color>();
}

status colordef_(state2& st, const vector<string>& tokens, Paren p)
{
	if(tokens.size() < 2)
	{
		cerr << "Meta info 'colordef' needs arguments" << endl; cout << endl;
		return INVALID_META;
	}
	for(size_t i = 1; i < tokens.size(); i += 2) //parse two tokens at once
	{
		bool default_col = false;
		if(tokens[i] == (string)"(" && tokens[i+1] == (string)")")
		{
			i++; // increment one more
			default_col = true;
		}
		Maybe<Color> co = get_color(tokens[i+1]);
		if(co.isNothing())
		{
			cerr << "Invalid color name '" << tokens[i+1] << "' inside a meta info 'colordef'" << endl; cout << endl;
			return INVALID_META;
		}
		Color col = co.unJust();
		if(default_col)
		{
			st.palette.default_color = col;
		}
		else
		{
			const string& str = tokens[i];
			for(size_t j = 0; j < str.size(); j++)
			{
				if(st.palette.p.find(str[j]) == st.palette.p.end() || st.palette.p[str[j]] == Null)
				{
					st.palette.p[str[j]] = col;
					cout << "colordef: '" << str[j] << "' is " << col_to_str(col) << endl;
				}
				else
				{
					cerr << "conflicting colordef: " << 
						col_to_str(col) << " and " << col_to_str(st.palette.p[str[j]]) << " assigned to '" << str[j] << "'" << endl; cout << endl;
				}
			}
		}
		
	}
	return ALL_OK;
}




