#include "fileselect.h"
#include <iostream>
#include <sstream>
using namespace std;

error_level file_select(string& filename, const state& st)
{
	size_t size = st.content.size();
	
	switch(size) {
	case 0:
		cerr << "No files loaded." << endl; cout << endl;
		return NO_FILES_LOADED;
		break; // consistency
		
	case 1:
		filename = st.content.begin()->first;
		return ALL_OK;
		break; // consistency
		
	default:
		break;
	}
	
	cout << "Which file?" << endl;
	typedef size_t Index;
	
	Index i = 1;
	map<Index, string> map_;
	for(const auto& pa : st.content) {
		cout << '\t' << i << ": \"" << pa.first << '"' << endl;
		map_[i] = pa.first;
		i++;
	}
	Index max_plus_1 = i;
	
	cout << ">>> " << flush;
	
	string str;
	getline(cin, str);
	
	stringstream s2(str.c_str());
	Index inp;
	s2 >> inp;
	if(inp < 1 || inp >= max_plus_1) {
		cerr << "No such index." << endl; cout << endl;
		return NO_SUCH_INDEX;
	} else {
		filename = map_[inp];
		return ALL_OK;
	}
}
