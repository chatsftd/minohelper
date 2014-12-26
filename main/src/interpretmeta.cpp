#include "interpretmeta.h"
#include "parsemeta.h"
using namespace std;
static vector<string> tokenize(const string& str);
static status interpretmeta2(state2& st, meta m);

static status colordef_(state2& st, const vector<string>& tokens, Paren p)
{
	return ALL_OK;
}

static status direction_(state2& st, const vector<string>& tokens, Paren p)
{
	return ALL_OK;
}

static status comment_(state2& st, const vector<string>& tokens, Paren p)
{
	string last_token = tokens[tokens.size()-1];
	if(last_token[last_token.size()-1] != '-')
	{
		cerr << "The comment is unterminated." << endl;
		return SOMETHING_WRONG;
	}
	return ALL_OK;
}

static status interpretmeta2(state2& st, meta m)
{
	vector<string> tokens = tokenize(m.content);
	Paren p = m.paren;
	
	if(tokens.empty()){ return ALL_OK; }
#define if2(a) if(tokens[0] == string(a))
	if(tokens[0][0] == '-' && p == Brace)
	{
		return comment_  (st,tokens,p); 
	}
	else if2("colordefine"){ return colordef_ (st,tokens,p); }
	else if2("colordef"   ){ return colordef_ (st,tokens,p); }
	else if2("direction"  ){ return direction_(st,tokens,p); }
	else if2("dir"        ){ return direction_(st,tokens,p); }
	else
	{
		cerr << "Warning: unknown meta info " << m << endl;
	}
	
	return ALL_OK;
}

status interpretmeta(state2& st, vector<string>& plane)
{
	SyntaxTree2 tree2;
	status s = parsemeta(tree2,plane);
	if(s != ALL_OK) return s; 
	for(size_t i = 0, n = tree2.size(); i < n; i++)
	{
		cout << "meta #" << (i+1) << ": " << tree2[i] << endl;
		status s2 = interpretmeta2(st,tree2[i]);
		if(s2 != ALL_OK) return s2;
	}
	return ALL_OK;
}

static vector<string> tokenize(const string& str)
{
	vector<string> res;
	string tmp = "";
	static const string empty = "";
	for(size_t i = 0, n = str.size(); i < n; i++)
	{
		char c = str[i];
		switch(c)
		{
			case ' ' : /*FALLTHROUGH*/
			case '\t':
				if(!tmp.empty())
				{
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
				if(!tmp.empty())
				{
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
	return res;
}


