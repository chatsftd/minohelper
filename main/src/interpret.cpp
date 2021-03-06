#include "interpret.h"
#include "import.h"
#include "export.h"
#include "help.h"
#include "config.h"
#include "type/args.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

static error_level status_(state& st, const arguments2& /*args**/)
{
	size_t size = st.content.size();
	if(!size) {
		cout << "No files loaded." << endl;
	} else {
		cout << "Loaded " << (size == 1 ? "file" : "files") << ":" << endl;
		for(const auto& pa : st.content) {
			cout << "\t\"" << pa.first << '"' << endl;
		}
		cout << endl;
	}
	
	error_level s = st.error_status;
	cout << "Error code: " << s << '(' << (int)s << ')' << endl << endl;
	return s; // inherit the error level
}

static error_level exit_(state& st, const arguments2& args)
{
	if(args.size() < 2) { return EXIT_ALL; }
	stringstream ss(args[1].c_str());
	int num;
	ss >> num;
	if(!ss) { return EXIT_ALL; }
	else {
		st.error_status = static_cast<error_level_i>(num);
		return EXIT_ALL;
	}
	
}

error_level interpret(state& st, const string& a)
{
	arguments2 args;
	args.parse(a);
	
	if(args.empty()) {return ALL_OK;}
#define if2(a) if(args[0] == string(a))
	if2("exit"  ) return   exit_(st,args);
	else if2("import") return import_(st,args);
	else if2("export") return export_(st,args);
	else if2("status") return status_(st,args);
	else if2("help"  ) return   help_(st,args);
	else if2("config") return config_(st,args);
	else {
		cerr << "\"" << args[0] << "\" is not a valid command." << endl; cout << endl;
		return NO_SUCH_COMMAND;
	}
}
