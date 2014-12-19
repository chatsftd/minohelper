#include "interpretmeta.h"
#include "parsemeta.h"
using namespace std;

static vector<string> tokenize(string str)
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
		}
	}
	return res;
}

status interpretmeta(state& st, vector<string>& plane)
{
	SyntaxTree2 tree2;
	status s = parsemeta(tree2,plane);
	for(size_t i = 0, n = tree2.size(); i < n; i++)
	{
		cout << "meta #" << (i+1) << ": " << paren_begin(tree2[i].first) << tree2[i].second << paren_end(tree2[i].first) << endl;
		
		vector<string> tokens = tokenize(tree2[i].second);
		/* fixme: modify state using tokens*/
	}
	return s;
}
