#include "help.h"
#include "parsearg.h"
#include <iostream>
using namespace std;

static const char help[] = (
 "usage: <command> [<args>]\n"
 "Available Commands:\n"
 "     import   Import file(s) to minohelper\n"
 "     export   Export file(s) from minohelper\n"
 "     exit     Exit minohelper\n"
 "     status   Display minohelper's status\n"
 "     help     Display this list\n"
 "     config   Set, get and list the config\n"
 "\n"
 "For more information, see 'help <command>'.\n"
 );

status help_(state& /*st**/, const arguments2& args)
{
	ret_data ret;
	arg_info info;
	status s2 = ret.parse_arg2(info,args);
	if(s2 != ALL_OK) return s2;
	
	vector<vector<string> > opts = ret.options();
	if(opts.empty())
	{
		cout << help << endl;
		return ALL_OK;
	}
	vector<string> opt = opts[0];
	string command = opt[1];
	
	if(command == "import")
	{
		cout << ( 
			"usage: import [<files>]\n"
			"  Import file(s) to minohelper\n"
			"  If called with no arguments, it will ask for one.\n"
			) << endl;
		return ALL_OK;
	}
	else if(command == "export")
	{
		cout << ( 
			"usage: export [<source>] [-o <destination>]\n"
			"  Export file(s) from minohelper\n"
			"  If called without destination, it will ask for one;\n"
			"  if called without source, it will ask you to choose one.\n"
			) << endl;
		return ALL_OK;
	}
	else if(command == "exit")
	{
		cout << ( 
			"usage: exit\n"
			"  Exit minohelper\n"
			) << endl;
		return ALL_OK;
	}
	else if(command == "status")
	{
		cout << ( 
			"usage: status\n"
			"  Display minohelper's status\n"
			"  Currently, this command displays the following things:\n"
			"    loaded files\n"
			"    error code of the last command\n"
			) << endl;
		return ALL_OK;
	}
	else if(command == "help")
	{
		cout << ( 
			"usage: help [<command>]\n"
			"  Display a command's detailed help\n"
			"  If called with no arguments, it will display the list.\n"
			) << endl;
		return ALL_OK;
	}
	else if(command == "config")
	{
		cout << ( 
			"usage: config --set <varname> <value>\n"
			"       config --get <varname>\n"
			"       config --list\n"
			"  Set, get and list the config\n"
			//"  If called with no arguments, it will display this help.\n"
			) << endl;
	}
	else
	{
		cerr << "\"" << command << "\" is not a valid command." << endl; cout << endl;
		return NO_SUCH_COMMAND;
	}
	
	return ALL_OK;
}
