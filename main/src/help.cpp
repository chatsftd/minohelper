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

string help_message(const string& command)
{ 
	if(command == "import")
	{
		return( 
			"usage: import [<files>]\n"
			"  Import file(s) to minohelper\n"
			"  If called with no arguments, it will ask for one.\n"
			);
	}
	else if(command == "export")
	{
		return( 
			"usage: export [<source>] [-o <destination>]\n"
			"  Export file(s) from minohelper\n"
			"  If called without destination, it will ask for one;\n"
			"  if called without source, it will ask you to choose one.\n"
			);
	}
	else if(command == "exit")
	{
		return( 
			"usage: exit\n"
			"  Exit minohelper\n"
			);
	}
	else if(command == "status")
	{
		return( 
			"usage: status\n"
			"  Display minohelper's status\n"
			"  Currently, this command displays the following things:\n"
			"    loaded files\n"
			"    error code of the last command\n"
			);
	}
	else if(command == "help")
	{
		return( 
			"usage: help [<command>]\n"
			"  Display a command's detailed help\n"
			"  If called with no arguments, it will display the list.\n"
			);
	}
	else if(command == "config")
	{
		return( 
			"usage: config --set <varname> <value>\n"
			"       config --get <varname>\n"
			"       config --list\n"
			"  Set, get and list the config\n"
			"  If called with no arguments, it will display this help.\n"
			);
	}
	else{ return "";}
}  

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
	string text = help_message(command);
	if(text.empty())
	{
		cerr << "\"" << command << "\" is not a valid command." << endl; cout << endl;
		return NO_SUCH_COMMAND;
	}
	else
	{
		cout << text << endl;
		return ALL_OK;
	}
}
