#include "import.h"
#include <iostream>
#include <fstream>
using namespace std;

int import_(const vector<string>& vec)
{
	cout << "command \"import\" was called." << endl;
	
	int ret_val = 0;
	for(size_t j = 1; j < vec.size(); ++j)
	{
		cout << "argument #" << j << " is \"" << vec[j] << '"' << endl;
		ifstream ifs(vec[j].c_str());
		if(!ifs)
		{
			cerr << "file \"" << vec[j] << "\" does not exist" << endl << endl;
			ret_val = -2; // doesn't-exist error
			continue;
		}
		
		
		cout << "the content of \"" << vec[j] << "\" is:" << endl;
		char ch;
		while((ch = ifs.get()) != EOF) cout << ch;
		cout << endl << endl;
	}
	return ret_val;
}
