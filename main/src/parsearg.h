#ifndef PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#define PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#include "type/status.h"
#include "type/args.h"
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::size_t> arg_info; 
typedef std::map<std::string, std::vector<std::vector<std::string> > > ret_data;

/*
 * args: "A","-o","abc","-i","B","-o","def","C","-p","123","456","-p","567","890","-i"
 * arg_info: '-o' takes one argument, '-i' takes none...
 * ret_data: {"": [["A"],["B"],["C"]], "-o": [["abc"],["def"]], "-p": [["123","456"],["567","890"]], "-i": [[],[]]}
 */
std::string last_valid(std::vector<std::vector<std::string> > dat);
arg_info default_arg_info();
status parse_arg2(const arg_info& info, ret_data& ret, const arguments2& args);

status parse_arg(std::string& input, std::string& output, const arguments2& args);

#endif/*PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88*/
