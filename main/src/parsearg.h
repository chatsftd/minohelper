#ifndef PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#define PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#include "type/errorlevel.h"
#include "type/args.h"
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::size_t> arg_info;

class ret_data
{
	std::vector<std::vector<std::string> > options_;
	
public:
	ret_data() : options_() {}
	std::string last_valid(const std::string& opt);
	std::vector<std::vector<std::string> > options();
	std::vector<std::vector<std::string> > options(const std::string& opt);
	error_level parse_arg2(const arg_info& info, const arguments2& args);
};

/*
 * args: "A","-o","abc","-i","B","-o","def","C","-p","123","456","-p","567","890","-i"
 * arg_info: '-o' takes one argument, '-i' takes none...
 * ret_data: [["","A"],["-o","abc"],["-i"],["","B"],["-o","def"],["","C"],["-p","123","456"],["-p","567","890"],["-i"]]
 */

arg_info default_arg_info();



#endif/*PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88*/
