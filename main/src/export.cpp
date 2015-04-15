#include "fileselect.h"
#include "export.h"
#include "parsearg.h"
#include "import.h"
#include "mjsn.h"
#include "lib/debug.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
using namespace std;

error_level export_(state& st, const arguments2& args)
{
	parsed_args ret;
	arg_info info;
	info["-o"] = 1;
	info["--width"] = 1;
	
	error_level s2 = ret.parse_arg2(info,args);
	if(s2 != ALL_OK) return s2;
	
	const vector<vector<string> > inputs = ret.options("");
	string input;
	
	if(inputs.empty()) {
		error_level s = file_select(input, st);
		if(s != ALL_OK) return s;
	} else if(inputs.size() >= 2) {
		cerr << "Cannot determine which file to export." << endl; cout << endl;
		return INVALID_ARGS;
	} else {
		input = inputs[0][1];
	}
	
	if(st.content.find(input) == st.content.end()) { // if input is not found
		/*
		 * create args from thin air and
		 * import the file
		 */
		
		arguments2 new_args;
		new_args.push_back("import");
		new_args.push_back(input);
		
		error_level s9 = import_(st,new_args);
		if(s9 != ALL_OK) return s9;
	}
	
	const vector<vector<string> > outputs = ret.options("-o");
	if(outputs.size() >= 2) {
		cerr << "Cannot output to more than one file." << endl; cout << endl;
		return INVALID_ARGS;
	}
	
	string output;
	if(outputs.empty()) {
		cout << "To where?" << endl;
		cout << ">>> " << flush;
		getline(cin,output);
	} else {
		output = outputs[0][1];
	}
	
	const vector<vector<string> > widths = ret.options("--width");
	size_t max_width = 0;
	if(!widths.empty()) {
		string s = widths.back()[1];
		stringstream ss(s.c_str());
		ss >> max_width;
		if(!ss) {
			cerr << "'" << s << "' is not a valid width." << endl; cout << endl;
			return INVALID_ARGS;
		}
		
	}
	
	ofstream ofs(output.c_str());
	cout << "Exporting \"" << input << "\" to \"" << output << "\" ..." << endl;
	
	ofs << st.content[input].first.to_str(st.content[input].second,max_width) << endl;
	
	cout << "Finished." << endl << endl;
	return ALL_OK;
}
