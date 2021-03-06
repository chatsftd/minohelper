#include "mjsn.h"
#include <sstream>
using namespace std;

static string export4(const mino_with_dir& md, const color_palette& palette)
{
	mino m = md.first;
	direction d = md.second;
	stringstream ans;
	ans << '"' << palette.get_color_of(m.ch).to_int();
	ans << '_' << static_cast<int>(m.get_shape_num());
	ans << '_' << static_cast<int>(d);
	ans << '_' << m.top_left().column;
	ans << '_' << "0";
	ans << '"';
	return ans.str();
}

void mjsn::make_mjsn(const vector<mino_with_dir>& minos)
{
	size_t down_most = 0;
	for(size_t i = 0; i < minos.size(); ++i) { //look for down_most
		point p = minos[i].first.top_left();
		if(down_most < p.row) down_most = p.row;
	}
	
	vector< vector<mino_with_dir> > result(down_most+1);
	for(size_t i = 0; i < minos.size(); ++i) {
		point p = minos[i].first.top_left();
		result[down_most - p.row].push_back(minos[i]);
	}
	
	
	while(!result.empty()) { // remove empty vector<mino>
		if(result.back().empty()) result.pop_back();
		else break;
	}
	
	this->md_plane = result;
}

string mjsn::to_str(const color_palette& palette, const size_t& max_width) const
{
	vector<string> strs = {"[","\"\"",","};
	for(size_t j = 0; j < this->md_plane.size(); ++j) {
		if(this->md_plane[j].empty()) {
			strs.push_back("\"\",");
			continue;
		}
		strs.push_back("[");
		
		for(size_t k = 0; k < this->md_plane[j].size(); ++k) {
			strs.push_back(export4(this->md_plane[j][k], palette));
			if(k+1 != this->md_plane[j].size()) {
				strs.push_back(",");
			}
		}
		strs.push_back("],");
	}
	strs.push_back("\"end\"");
	strs.push_back("]");
	
	string res;
	if(max_width) {
		string tmp;
		for(const auto& pa : strs) {
			if(tmp.size() + pa.size() <= max_width) {
				tmp += pa;
			} else if(pa.size() <= max_width) {
				res += tmp + "\n"; // add line
				tmp = pa;
			} else {
				res += tmp + "\n" + pa + "\n";
				tmp = "";
			}
		}
		res += tmp;
	} else {
		for(const auto& pa : strs) {
			res += pa;
		}
	}
	return res;
}

