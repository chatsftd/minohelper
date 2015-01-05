#include "interpret.h"
#include "import.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void init(state& st, const vector<string>& v)
{
	vector<string> vec;
	vec.push_back("import");
	for(size_t k = 0; k < v.size(); k++)
	{
		vec.push_back(v[k]);
	}
	status s = import_(st,vec);
	st.error_status = s;
}

int main(int argc, char** argv)
{
	state st;
	if(argc >= 2)
	{
		vector<string> vec;
		for(int k = 1; k < argc; k++)
		{
			vec.push_back(argv[k]);
		}
		init(st,vec);
	}
	
	while(true)
	{
		string tmp = "";
		cout << "> " << flush;
		getline(cin,tmp);
		status s = interpret(st,tmp);
		st.error_status = s;
		switch(s)
		{
			case EXIT_ALL: goto end; /* escape from while-true */
			default: break; /* do nothing */
		}
	}
	
	end: return 0;
}
