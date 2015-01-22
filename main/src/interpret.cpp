#include "interpret.h"
#include "import.h"
#include "export.h"
#include "help.h"
#include "type/args.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

static status status_(state& st, const arguments2& args)
{
	size_t size = st.content.size();
	if(!size)
	{
		cout << "No files loaded." << endl;	
	}
	else
	{
		cout << "Loaded " << (size == 1 ? "file" : "files") << ":" << endl;		
		for(map<string,data>::const_iterator it = st.content.begin(); it != st.content.end(); ++it)
		{
			cout << "\t\"" << (it->first) << '"' << endl;
		}
		cout << endl;
	}
	
	status s = st.error_status;
	cout << "Error code: " << s << '(' << (int)s << ')' << endl << endl;
	return s; // inherit the status
}

status interpret(state& st, const string& a)
{
	arguments2 args;
	args.parse(a);
	
	if(args.empty()){return ALL_OK;}
#define if2(a) if(args[0] == string(a))	
	if2("exit")
	{
		return EXIT_ALL;
	}
	else if2("import") return import_(st,args);
	else if2("export") return export_(st,args);
	else if2("status") return status_(st,args);
	else if2("help"  ) return   help_(st,args);
	else
	{
		cerr << "\"" << args[0] << "\" is not a valid command." << endl; cout << endl;
		return NO_SUCH_COMMAND;
	}
}
