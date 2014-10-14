#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	string a = "";
	while(true)
	{
		cout << "> " << flush;
		getline(cin,a);
		if(a == string("exit")){break;}
		cout << "input is \"" << a << '"' << endl;
	}
	return 0;
}
