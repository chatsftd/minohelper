#include "fileselect.h"
#include "export.h"
#include "parsearg.h"
#include "import.h"
#include "mjsn.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


static string export3(state::file_data dat)
{
	mjsn m;
	m.make_mjsn(dat.minos);
	return m.to_str(dat.palette);
}

error_level export_(state& st, const arguments2& args)
{
	ret_data ret;
	error_level s2 = ret.parse_arg2(default_arg_info(),args);
	if(s2 != ALL_OK) return s2;
	
	string input  = ret.last_valid("");
	string output = ret.last_valid("-o");
	if(input == "")
	{
		error_level s = file_select(input, st);
		if(s != ALL_OK) return s;
	}
	
	if(st.content.find(input) == st.content.end()) // if input is not found
	{
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
	
	if(output == "")
	{
		cout << "To where?" << endl;
		cout << ">>> " << flush;
		getline(cin,output);
	}
	
	ofstream ofs(output.c_str());
	cout << "Exporting \"" << input << "\" to \"" << output << "\" ..." << endl;
	
	
	ofs << export3(st.content[input]) << endl;
	cout << "Finished." << endl << endl;
	return ALL_OK;
}
