#ifndef PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#define PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#include "type/errorlevel.h"
#include "type/args.h"
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::size_t> arg_info;

class parsed_args
{
	std::vector<std::vector<std::string> > options_;
	
public:
	parsed_args() : options_() {}
	std::vector<std::vector<std::string> > options() const;
	std::vector<std::vector<std::string> > options(const std::string& opt) const;
	error_level parse_arg2(const arg_info& info, const arguments2& args);
};

/*
 * args: "A","-o","abc","-i","B","-o","def","C","-p","123","456","-p","567","890","-i"
 * arg_info: '-o' takes one argument, '-i' takes none...
 * parsed_args: [["","A"],["-o","abc"],["-i"],["","B"],["-o","def"],["","C"],["-p","123","456"],["-p","567","890"],["-i"]]
 */

arg_info default_arg_info();



#endif/*PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88*/
