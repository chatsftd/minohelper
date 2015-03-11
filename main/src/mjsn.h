#ifndef MJSN_H_DEFINED_D1462381BE2B141290C21DBDCDCA3BC33D95A467 
#define MJSN_H_DEFINED_D1462381BE2B141290C21DBDCDCA3BC33D95A467
#include "state.h"
#include <vector>
#include <string>

struct mjsn
{
	std::vector< std::vector<mino> > inside;
	void make_mjsn(const std::vector<mino>& minos);
	std::string to_str(const color_palette& palette) const;
};


#endif/*MJSN_H_DEFINED_D1462381BE2B141290C21DBDCDCA3BC33D95A467*/
