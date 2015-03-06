#ifndef PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100
#define PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100
#include "meta.h"
#include <vector>
#include <string>

typedef std::vector<meta> all_meta;

error_level parsemeta(all_meta& st, std::vector<std::string>& plane);

#endif/*PARSEMETA_H_DEFINED_C9564D0209E6A24CE123668EB6AB9102A6476100*/
