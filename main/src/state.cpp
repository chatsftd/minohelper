#include "state.h"

#include <iostream>
using namespace std;

state::state(void) : content() {}

data::data(void) : minos() {}
data::data(const std::vector<mino>& minos_) : minos(minos_) {}
