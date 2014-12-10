#include "paren.h"
using namespace std;
status paren(state& st, vector<string>& plane)
{
	for(size_t i = 0, n = plane.size(); i < n; i++)
	{
		for(size_t j = 0, m = plane[i].size(); j < m; j++)
		{
			char c = plane[i][j];
			switch(c)
			{
				case '(': /*FALLTHROUGH*/
				case ')': /*FALLTHROUGH*/
				case '{': /*FALLTHROUGH*/
				case '}': /*FALLTHROUGH*/
				case '[': /*FALLTHROUGH*/
				case ']':
					cerr << "\"" << c << "\" is a reserved character and cannot be used to represent a mino." << endl << endl;
					return SOMETHING_WRONG;
			}
		}
	}
	return ALL_OK;
}
