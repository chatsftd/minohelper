#include "parsemeta.h"
#include <stack>
using namespace std;

error_level parsemeta(all_meta& st, vector<string>& plane)
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
				case '(': if(paren_stack.empty()){ st.push_back(meta(Parenthesis, point(i,j))); ignore_open = true; } paren_stack.push(Parenthesis); break;
				case '{': if(paren_stack.empty()){ st.push_back(meta(Brace      , point(i,j))); ignore_open = true; } paren_stack.push(Brace      ); break;
				case '[': if(paren_stack.empty()){ st.push_back(meta(Bracket    , point(i,j))); ignore_open = true; } paren_stack.push(Bracket    ); break;
				
				case ')': /*FALLTHROUGH*/
				case '}': /*FALLTHROUGH*/
				case ']':
					if(paren_stack.empty() || paren_end(paren_stack.top()) != c)
					{
						cerr << "At " << point(i,j) << ": \"" << c << "\" is unmatched." << endl; cout << endl;
						return INVALID_META;
					}
					
					paren_stack.pop();
					
					if(paren_stack.empty())
					{
						st.back().set_last_pos(point(i,j));
					}
					
					ignore_close = true;
					break;
			}
			
			if(!paren_stack.empty() && !ignore_open){ st.back().content += c; }
			plane2[i] += paren_stack.empty() && !ignore_close ? c : ' ';
		}
		if(!paren_stack.empty()){ st.back().content += '\n';}
	}
	plane = plane2;
	return ALL_OK;
}
