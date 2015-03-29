#ifndef MERGE_SEGMENT_H_DEFINED_B55426BCA554843245E9542E0E7318F8B6D57FE8
#define MERGE_SEGMENT_H_DEFINED_B55426BCA554843245E9542E0E7318F8B6D57FE8
#include "../mjsn.h"

struct mino_map_segment {
	std::vector<mino> minos;
	point last_pos;
	direction dir;
	mino_map_segment(std::vector<mino> m, point p, direction d) : minos(m), last_pos(p), dir(d) {}
};

enum merge_status {
	MERGE_SUCCESS,
	MERGE_CONFLICT,
	MERGE_NOT_FOUND
};

std::vector<mino_with_dir> add_dir(const std::vector<mino>& minos, direction dir);
error_level merge_segments(std::vector<mino_with_dir>& mds, const std::vector<mino_map_segment>& segments, const label_info& labels);


#endif/*MERGE_SEGMENT_H_DEFINED_B55426BCA554843245E9542E0E7318F8B6D57FE8*/
