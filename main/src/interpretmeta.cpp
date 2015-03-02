#include "interpretmeta.h"
#include "parsemeta.h"
#include "colordef.h"
#include "lib/maybe.h"
using namespace std;
static error_level interpretmeta2(state2& st, const meta& m);

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

static error_level direction_(state2& st, const meta& m)
{
	const vector<string> tokens = m.get_tokens();
	if(tokens.size() < 2)
	{
		cerr << "Meta info 'direction' needs an argument" << endl; cout << endl;
		return INVALID_META;
	}
	
	Maybe<direction> mdir = str_to_dir(tokens[1]);
	if(mdir.isNothing())
	{
		cerr << "Invalid direction '" << tokens[1] << "' inside a meta info 'direction'" << endl; cout << endl;
		return INVALID_META;
	}
		
	direction dir = mdir.unJust();
	st.dir.set_direction(m.pos,dir);
	cout << "direction: " << dir_to_str(dir) << " after " << m.pos << endl;
	
	
	return ALL_OK; // fixme
}

static error_level comment_(state2& /*st**/, const meta& m)
{
	const string last_token = m.get_tokens().back();
	if(last_token[last_token.size()-1] != '-')
	{
		cerr << "The comment is unterminated." << endl; cout << endl;
		return INVALID_META;
	}
	return ALL_OK;
}

static error_level interpretmeta2(state2& st, const meta& m)
{
	const vector<string> tokens = m.get_tokens();
	Paren p = m.paren;
	
	if(tokens.empty()){ return ALL_OK; }
#define if2(a) if(tokens[0] == string(a))
	if(tokens[0][0] == '-' && p == Brace)
	{
		return comment_  (st,m);
	}
	else if2("colordefine"){ return colordef_ (st,m); }
	else if2("colordef"   ){ return colordef_ (st,m); }
	else if2("direction"  ){ return direction_(st,m); }
	else if2("dir"        ){ return direction_(st,m); }
	else
	{
		cerr << "Warning: unknown meta info " << m << endl;
	}
	
	return ALL_OK;
}

error_level interpretmeta(state2& st, vector<string>& plane)
{
	all_meta tree2;
	error_level s = parsemeta(tree2,plane);
	if(s != ALL_OK) return s;
	for(size_t i = 0, n = tree2.size(); i < n; i++)
	{
		cout << "meta #" << (i+1) << ": " << tree2[i] << endl;
		error_level s2 = interpretmeta2(st,tree2[i]);
		if(s2 != ALL_OK) return s2;
	}
	return ALL_OK;
}

