#include "colordef.h"
#include "../lib/maybe.h"
#include <iostream>
using namespace std;

static Maybe<Color> get_color(const string& str)
{
#define if2(a) if(str == static_cast<string>(a))
	if2("r") return Just<Color>(RED);
	if2("o") return Just<Color>(ORANGE);
	if2("y") return Just<Color>(YELLOW);
	if2("g") return Just<Color>(GREEN);
	if2("l") return Just<Color>(LIGHTBLUE);
	if2("n") return Just<Color>(NAVY);
	if2("p") return Just<Color>(PURPLE);
	if2("b") return Just<Color>(BLACK);
	if2("w") return Just<Color>(WHITE);
	if2("h") return Just<Color>(HEAL);
	if2("red") return Just<Color>(RED);
	if2("ora") return Just<Color>(ORANGE);
	if2("yel") return Just<Color>(YELLOW);
	if2("gre") return Just<Color>(GREEN);
	if2("lig") return Just<Color>(LIGHTBLUE);
	if2("nav") return Just<Color>(NAVY);
	if2("blu") return Just<Color>(NAVY);
	if2("pur") return Just<Color>(PURPLE);
	if2("vio") return Just<Color>(PURPLE);
	if2("bla") return Just<Color>(BLACK);
	if2("whi") return Just<Color>(WHITE);
	if2("hea") return Just<Color>(HEAL);
	if2("pin") return Just<Color>(HEAL);
	if2("orange") return Just<Color>(ORANGE);
	if2("yellow") return Just<Color>(YELLOW);
	if2("green") return Just<Color>(GREEN);
	if2("lightblue") return Just<Color>(LIGHTBLUE);
	if2("navy") return Just<Color>(NAVY);
	if2("blue") return Just<Color>(NAVY);
	if2("purple") return Just<Color>(PURPLE);
	if2("violet") return Just<Color>(PURPLE);
	if2("black") return Just<Color>(BLACK);
	if2("white") return Just<Color>(WHITE);
	if2("heal") return Just<Color>(HEAL);
	if2("pink") return Just<Color>(HEAL);
	else return Nothing<Color>();
}

error_level colordef_(state2& st, const meta& m)
{
	const vector<string> tokens = m.get_tokens();
	if(tokens.size() < 2) {
		cerr << "Meta info 'colordef' needs arguments" << endl; cout << endl;
		return INVALID_META;
	}
	for(size_t i = 1; i < tokens.size(); i += 2) { //parse two tokens at once
		bool default_col = false;
		if(tokens[i] == (string)"(" && tokens[i+1] == (string)")") {
			i++; // increment one more
			default_col = true;
		}
		Maybe<Color> co = get_color(tokens[i+1]);
		if(co.isNothing()) {
			cerr << "Invalid color name '" << tokens[i+1] << "' inside a meta info 'colordef'" << endl; cout << endl;
			return INVALID_META;
		}
		Color col = co.unJust();
		if(default_col) {
			st.palette.default_color = col;
		} else {
			const string& str = tokens[i];
			for(size_t j = 0; j < str.size(); j++) {
				if(!st.palette.exist(str[j])) {
					st.palette.set_color_of(str[j],col);
					cout << "colordef: '" << str[j] << "' is " << col << endl;
				} else {
					cerr << "conflicting colordef: " << col << " and " << st.palette.get_color_of(str[j]) << " assigned to '" << str[j] << "'" << endl; cout << endl;
				}
			}
		}
		
	}
	return ALL_OK;
}




