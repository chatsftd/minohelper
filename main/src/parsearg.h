#ifndef PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#define PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88
#include "type/status.h"
#include "type/args.h"
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::size_t> arg_info; 
typedef std::map<std::string, std::vector<std::vector<std::string> > > ret_data;

status parse_arg2(const arg_info& info, ret_data& ret, const arguments2& args);

status parse_arg(std::string& input, std::string& output, const arguments2& args);

#endif/*PARSEARG_H_DEFINED_EB1F28CC7DDEDAD49229495C94BD0C7875C30C88*/
