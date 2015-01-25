#ifndef PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#define PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#include "type/status.h"
#include "type/args.h"
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::size_t> arg_info; 

class ret_data
{
	std::map<std::string, std::vector<std::vector<std::string> > > inside;

public:
	ret_data() : inside() {}
	std::string last_valid(std::string opt);
	status parse_arg2(const arg_info& info, const arguments2& args);
};

/*
 * args: "A","-o","abc","-i","B","-o","def","C","-p","123","456","-p","567","890","-i"
 * arg_info: '-o' takes one argument, '-i' takes none...
 * ret_data: {"": [["A"],["B"],["C"]], "-o": [["abc"],["def"]], "-p": [["123","456"],["567","890"]], "-i": [[],[]]}
 */

arg_info default_arg_info();



#endif/*PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88*/
