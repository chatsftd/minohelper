#include "parsemeta.h"
using namespace std;

status paren2(SyntaxTree2& st, vector<string>& plane)
{
	stack<Paren> paren_stack;
	vector<string> plane2;
	for(size_t i = 0, n = plane.size(); i < n; i++)
	{
		plane2.push_back("");
		for(size_t j = 0, m = plane[i].size(); j < m; j++)
		{
			char c = plane[i][j];
			bool ignore_close = false;
			bool ignore_open  = false;
			switch(c)
			{
				case '(': if(paren_stack.empty()){ st.push_back(meta(Parenthesis,"")); } paren_stack.push(Parenthesis); ignore_open = true; break;
				case '{': if(paren_stack.empty()){ st.push_back(meta(Brace      ,"")); } paren_stack.push(Brace      ); ignore_open = true; break;
				case '[': if(paren_stack.empty()){ st.push_back(meta(Bracket    ,"")); } paren_stack.push(Bracket    ); ignore_open = true; break;
				
				case ')': /*FALLTHROUGH*/
				case '}': /*FALLTHROUGH*/
				case ']':
					if(paren_stack.empty() || end(paren_stack.top()) != c)
					{
						cerr << "At " << point(i,j) << ": \"" << c << "\" is unmatched." << endl << endl;
						return SOMETHING_WRONG;
					}
					paren_stack.pop(); 
					ignore_close = true;
					break;
			}
			
			if(!paren_stack.empty() && !ignore_open){ st[st.size()-1].second += c; }
			plane2[i] += paren_stack.empty() && !ignore_close ? c : ' ';
		}
		if(!paren_stack.empty()){ st[st.size()-1].second += ' ';} // newline becomes space
	}
	plane = plane2;
	return ALL_OK;
}

char begin(Paren p)
{
	switch(p)
	{
		case Parenthesis: return '(';
		case Bracket: return '[';
		default: return '{';
	}
}

char end(Paren p)
{
	switch(p)
	{
		case Parenthesis: return ')';
		case Bracket: return ']';
		default: return '}';
	}
}
