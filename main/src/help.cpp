#include "help.h"
#include <iostream>
using namespace std;

static const char help[] = (
 "usage: <command> [<args>]\n"
 "Available Commands:\n"
 "     import   Import file(s) to minohelper\n"
 "     export   Export file(s) to minohelper\n"
 "     exit     Exit minohelper\n"
 "     status   Display former command's error code\n"
 "     help     Display this list\n"
 );

status help_(state& st, const std::vector<std::string>& vec)
{
	cout << help << endl;
	return ALL_OK;
}
