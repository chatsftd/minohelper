#ifndef MJSN_H_DEFINED_D1462381BE2B141290C21DBDCDCA3BC33D95A467
#define MJSN_H_DEFINED_D1462381BE2B141290C21DBDCDCA3BC33D95A467
#include "mino.h"
#include "type/errorlevel.h"
#include "meta/state2.h"
#include <vector>
#include <string>
#include <utility>

typedef std::pair<mino,direction> mino_with_dir;

struct mjsn {
	std::vector< std::vector<mino_with_dir> > inside;
	void make_mjsn(const std::vector<mino_with_dir>& minos);
	std::string to_str(const color_palette& palette) const;
};


#endif/*MJSN_H_DEFINED_D1462381BE2B141290C21DBDCDCA3BC33D95A467*/
