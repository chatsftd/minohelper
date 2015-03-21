#include "direction.h"
#include "../lib/maybe.h"
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

static string dir_to_str(direction dir)
{
	switch(dir)
	{
		case TO_SOUTH: return "to_south";
		case TO_EAST : return "to_east" ;
		case TO_NORTH: return "to_north";
		default      : return "to_west" ;
	}
}

static Maybe<direction> str_to_dir(const string& str)
{ 
#define if2(a) if(str == static_cast<string>(a))
#define JD(a) Just<direction>(a)
	if2("tosouth"){ return JD(TO_SOUTH); }
	if2("toeast" ){ return JD(TO_EAST ); }
	if2("tonorth"){ return JD(TO_NORTH); }
	if2("towest" ){ return JD(TO_WEST ); }
	
	if2("fromnorth"){ return JD(TO_SOUTH); }
	if2("fromwest" ){ return JD(TO_EAST ); }
	if2("fromsouth"){ return JD(TO_NORTH); }
	if2("fromeast" ){ return JD(TO_WEST ); }
	
	if2("tobottom"){ return JD(TO_SOUTH); }
	if2("toright" ){ return JD(TO_EAST ); }
	if2("totop"   ){ return JD(TO_NORTH); }
	if2("toleft"  ){ return JD(TO_WEST ); }
	
	if2("fromtop"   ){ return JD(TO_SOUTH); }
	if2("fromleft"  ){ return JD(TO_EAST ); }
	if2("frombottom"){ return JD(TO_NORTH); }
	if2("fromright" ){ return JD(TO_WEST ); }
	else return Nothing<direction>();
#undef if2	
} 

error_level direction_(state2& st, const meta& m)
{
	const vector<string> tokens = m.get_tokens();
	if(tokens.size() < 2)
	{
		cerr << "Meta info 'direction' needs an argument" << endl; cout << endl;
		return INVALID_META;
	}
	if(tokens.size() % 2) //odd number == "direction" + even number 
	{
		cerr << "Meta info 'direction' needs odd number of arguments" << endl; cout << endl;
		return INVALID_META;
	}
	
	Maybe<direction> mdir = str_to_dir(tokens[1]);
	if(mdir.isNothing())
	{
		cerr << "Invalid direction '" << tokens[1] << "' inside a meta info 'direction'" << endl; cout << endl;
		return INVALID_META;
	}
		
	direction dir = mdir.unJust();
	st.dir.set_direction(m.first_pos,dir);
	st.dir.set_transform(m.first_pos,m.last_pos);
	cout << "direction: " << dir_to_str(dir) << " after " << m.first_pos << endl;
	
	const string col_or_row = static_cast<int>(dir)%2 ? "column" : "row";
	for(size_t i = 2; i < tokens.size(); i += 2) //parse two tokens at once
	{
		const string label_name = tokens[i];
		stringstream ss(tokens[i+1]);
		int num;
		ss >> num;
		if(!ss)
		{
			cerr << "Invalid " << col_or_row << " number ";
			cerr << "'" << tokens[i+1] << "' inside a meta info 'direction'" << endl; cout << endl;
			return INVALID_META;
		}
		cout << "direction: label '" << tokens[i] << "' is at " << col_or_row << " " << num << endl;
		
		st.labels.set_label(tokens[i], num, m.last_pos, dir);
	}
	
	return ALL_OK; // fixme
}
