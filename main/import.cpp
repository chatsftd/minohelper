#include "import.h"
#include <iostream>
using namespace std;

int import_(const vector<string>& vec)
{
	cout << "command \"import\" was called." << endl;
	
	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "argument #" << j << " is \"" << vec[j] << '"' << endl;
	}
	return 0;
}
