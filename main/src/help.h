#ifndef HELP_H_DEFINED_F1FC336F79C37C83D065E055B36F9878D839C133
#define HELP_H_DEFINED_F1FC336F79C37C83D065E055B36F9878D839C133

#include "type/status.h"
#include "type/args.h"
#include "state.h"


status help_(state& st, const arguments2& args);
std::string help_message(const std::string& command);

#endif/*HELP_H_DEFINED_F1FC336F79C37C83D065E055B36F9878D839C133*/
