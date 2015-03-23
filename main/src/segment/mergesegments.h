#ifndef MERGE_SEGMENT_H_DEFINED_B55426BCA554843245E9542E0E7318F8B6D57FE8
#define MERGE_SEGMENT_H_DEFINED_B55426BCA554843245E9542E0E7318F8B6D57FE8
#include "../mjsn.h"
#include <set>

struct mino_map_segment
{
	std::vector<mino> minos;
	point last_pos;
	direction dir;
	mino_map_segment(std::vector<mino> m, point p, direction d) : minos(m), last_pos(p), dir(d) {}
};

enum merge_status
{
	MERGE_SUCCESS,
	MERGE_CONFLICT,
	MERGE_NOT_FOUND
};

struct label_table
{
	std::map<std::string,size_t> inside;
	label_table() : inside() {}
	label_table(std::map<std::string,size_t> i) : inside(i) {}
	bool empty() const { return this->inside.empty(); }
	size_t size() const { return this->inside.size(); }
	void add_offset(int x); 
};

std::set<std::string> common_labels(const label_table& t1, const label_table& t2);

class core
{
	std::vector<mino_with_dir> inside;
	label_table table;
	
public:
	core() : inside(), table() {}
	core(std::vector<mino_with_dir> i, std::map<std::string,size_t> l) : inside(i), table(l) {}
	core(const mino_map_segment& segment, const label_info& labels);
	std::vector<mino_with_dir> get_inside() const { return this->inside; }
	
	merge_status merge(const core& c);
};

std::vector<mino_with_dir> add_dir(const std::vector<mino>& minos, direction dir);
std::vector<mino_with_dir> merge_segments(const std::vector<mino_map_segment>& segments, label_info labels);


#endif/*MERGE_SEGMENT_H_DEFINED_B55426BCA554843245E9542E0E7318F8B6D57FE8*/
