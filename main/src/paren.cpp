#include "parsemeta.h"
#include "debug.h"
#include "paren.h"
#include "constructmino.h"
#include <stack>
#include <utility>
using namespace std;


status paren(state& st, vector<string>& plane)
{
	SyntaxTree2 tree2;
	status s = paren2(tree2,plane);
	for(size_t i = 0, n = tree2.size(); i < n; i++)
	{
		cout << "meta #" << (i+1) << ": " << begin(tree2[i].first) << tree2[i].second << end(tree2[i].first) << endl;
	}
	
	/* fixme: modify state using tree2*/
	return s;
}
