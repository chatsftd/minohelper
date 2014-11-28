#include "state.h"
using namespace std;

state::state(void) : content(), error_status(ALL_OK) {}

data::data(void) : minos() {}
data::data(const std::vector<mino>& minos_) : minos(minos_) {}
