#include "mjsn.h"
#include <sstream>
using namespace std;

static string export4(const mino& m, const color_palette& palette)
{
	stringstream ans;
	ans << '"' << palette.get_color_of(m.ch).to_int();
	ans << '_' << static_cast<int>(m.get_shape_num());
	ans << '_' << "0";
	ans << '_' << m.top_left().second;
	ans << '_' << "0";
	ans << '"';	
	return ans.str();
}

void mjsn::make_mjsn(const vector<mino>& minos)
{
	size_t down_most = 0;
	for(size_t i = 0; i < minos.size(); ++i) //look for down_most
	{
		point p = minos[i].top_left();
		if(down_most < p.first) down_most = p.first;
	}
	
	vector< vector<mino> > result(down_most+1);
	for(size_t i = 0; i < minos.size(); ++i)
	{
		point p = minos[i].top_left();
		result[down_most - p.first].push_back(minos[i]);
	}
	
	
	while(!result.empty()) // remove empty vector<mino>
	{
		if(result.back().empty()) result.pop_back();
		else break;
	}
	
	this->inside = result;
}

string mjsn::to_str(const color_palette& palette) const
{
	string str = "[\"\",";
	for(size_t j = 0; j < this->inside.size(); ++j)
	{
		if(this->inside[j].empty())
		{
			str += "\"\",";
			continue;
		}
		str += "[";
		
		for(size_t k = 0; k < this->inside[j].size(); ++k)
		{
			str += export4(this->inside[j][k], palette);
			if(k+1 != this->inside[j].size())
			{
				str += ",";
			}
		}
		str += "],";
	}
	str += "\"end\"]";
	return str;
}

