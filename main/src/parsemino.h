#ifndef PARSEMINO_H_DEFINED_2014_10_15_f327be3b1e0607c0a792e26fbedceee76442fc53
#define PARSEMINO_H_DEFINED_2014_10_15_f327be3b1e0607c0a792e26fbedceee76442fc53
#include "state.h"
#include "type/state2.h"
#include "lib/maybe.h"

Maybe<data> parse_mino(const state2& st2, const std::vector<std::string>& content);

#endif/*PARSEMINO_H_DEFINED_2014_10_15_f327be3b1e0607c0a792e26fbedceee76442fc53*/
