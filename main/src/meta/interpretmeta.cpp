#include "interpretmeta.h"
#include "parsemeta.h"
#include "colordef.h"
#include "direction.h"
#include "../lib/maybe.h"
#include <sstream>
using namespace std;
static error_level interpretmeta2(state2& st, const meta& m);



static error_level comment_(state2& /*st**/, const meta& m)
{
	const string last_token = m.get_tokens().back();
	if(last_token[last_token.size()-1] != '-') {
		cerr << "The comment is unterminated." << endl; cout << endl;
		return INVALID_META;
	}
	return ALL_OK;
}

static error_level interpretmeta2(state2& st, const meta& m)
{
	const vector<string> tokens = m.get_tokens();
	Paren p = m.paren;
	
	if(tokens.empty()) { return ALL_OK; }
#define if2(a) if(tokens[0] == string(a))
	if(tokens[0][0] == '-' && p == Brace) {
		return comment_  (st,m);
	} else if2("colordefine") { return colordef_ (st,m); }
	else if2("colordef"   ) { return colordef_ (st,m); }
	else if2("direction"  ) { return direction_(st,m); }
	else if2("dir"        ) { return direction_(st,m); }
	else {
		cerr << "Warning: unknown meta info " << m << endl;
	}
	
	return ALL_OK;
}

error_level interpretmeta(state2& st, vector<string>& plane)
{
	all_meta tree2;
	error_level s = parsemeta(tree2,plane);
	if(s != ALL_OK) return s;
	for(size_t i = 0, n = tree2.size(); i < n; i++) {
		cout << "meta #" << (i+1) << ": " << tree2[i] << endl;
		error_level s2 = interpretmeta2(st,tree2[i]);
		if(s2 != ALL_OK) return s2;
	}
	return ALL_OK;
}

