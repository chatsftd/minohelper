#include "export.h"
#include <iostream>
using namespace std;

status export_(state st, const vector<string>& vec)
{
	cout << "command \"export\" was called." << endl;
	
	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "argument #" << j << " is \"" << vec[j] << '"' << endl;
	}
	return ALL_OK;
}
