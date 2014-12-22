#include "interpretmeta.h"
#include "parsemeta.h"
using namespace std;
static vector<string> tokenize(const string& str);
static status interpretmeta2(state2& st, meta m);

static status interpretmeta2(state2& st, meta m)
{
	/* fixme: modify state using tokens*/
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


