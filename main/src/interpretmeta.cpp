#include "interpretmeta.h"
#include "parsemeta.h"
using namespace std;


status interpretmeta(state& st, vector<string>& plane)
{
	SyntaxTree2 tree2;
	status s = parsemeta(tree2,plane);
	for(size_t i = 0, n = tree2.size(); i < n; i++)
	{
		cout << "meta #" << (i+1) << ": " << paren_begin(tree2[i].first) << tree2[i].second << paren_end(tree2[i].first) << endl;
	}
	
	/* fixme: modify state using tree2*/
	return s;
}
