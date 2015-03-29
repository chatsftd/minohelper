#include "meta.h"
using namespace std;

char paren_begin(Paren p)
{
	switch(p) {
	case Parenthesis: return '(';
	case Bracket: return '[';
	default: return '{';
	}
}

char paren_end(Paren p)
{
	switch(p) {
	case Parenthesis: return ')';
	case Bracket: return ']';
	default: return '}';
	}
}

ostream& operator<<(ostream& o, const meta& m)
{
	return o << paren_begin(m.paren) << m.content << paren_end(m.paren) << " from " << m.first_pos << " to " << m.last_pos;
}

vector<string> meta::get_tokens() const
{
	vector<string> res;
	string tmp = "";
	static const string empty = "";
	for(size_t i = 0, n = this->content.size(); i < n; i++) {
		char c = this->content[i];
		switch(c) {
		case ' ' : /*FALLTHROUGH*/
		case '\t':
		case '\n':
			if(!tmp.empty()) {
				res.push_back(tmp);
				tmp = "";
			}
			break;
			
		case '(': /*FALLTHROUGH*/
		case '{': /*FALLTHROUGH*/
		case '[': /*FALLTHROUGH*/
		case ')': /*FALLTHROUGH*/
		case '}': /*FALLTHROUGH*/
		case ']':
			if(!tmp.empty()) {
				res.push_back(tmp);
				tmp = "";
			}
			res.push_back(empty + c);
			break;
			
		default:
			tmp += c;
			break;
		}
	}
	if(!tmp.empty()) {
		res.push_back(tmp);
		tmp = "";
	}
	return res;
}
