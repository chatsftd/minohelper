#include "state.h"
using namespace std;

state::state(void) : content(), error_status(ALL_OK) {}

data::data(void) : minos(), palette() {}
data::data(const std::vector<mino>& minos_, color_palette pal) : minos(minos_), palette(pal) {}
