#include "paren.h"
#include "constructmino.h"
#include <stack>
using namespace std;

enum Paren
{
	Parenthesis = ')', 
	Bracket     = ']',
	Brace       = '}'
};

status paren(state& st, vector<string>& plane)
{
	stack<Paren> paren_stack;
	vector<string> plane2;
	for(size_t i = 0, n = plane.size(); i < n; i++)
	{
		plane2.push_back("");
		for(size_t j = 0, m = plane[i].size(); j < m; j++)
		{
			char c = plane[i][j];
			bool ignore_me = false;
			switch(c)
			{
				case '(': paren_stack.push(Parenthesis); break;
				case '{': paren_stack.push(Brace      ); break;
				case '[': paren_stack.push(Bracket    ); break;
				
				case ')': /*FALLTHROUGH*/
				case '}': /*FALLTHROUGH*/
				case ']':
					if(paren_stack.empty() || static_cast<char>(paren_stack.top()) != c)
					{
						cerr << "At " << point(i,j) << ": \"" << c << "\" is unmatched." << endl << endl;
						return SOMETHING_WRONG;
					}
					paren_stack.pop(); 
					ignore_me = true;
					break;
			}
			plane2[i] += paren_stack.empty() && !ignore_me ? c : ' ';
		}
	}
	plane = plane2;
	return ALL_OK;
}
