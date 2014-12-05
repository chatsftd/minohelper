#include "constructmino.h"
#include "debug.h"

using namespace std;


mino::mino(const vector<point>& points, char c) : ch(c)
{
	assert2("mino size is not 4", points.size() == 4); 
	this->p0 = points[0];
	this->p1 = points[1];
	this->p2 = points[2];
	this->p3 = points[3];
}

ostream& operator<<(ostream& o, const point& p)
{
	assert2("Wrong point", p.first != WRONG_PLACE && p.second != WRONG_PLACE);
	return o << "(" << p.first+1 << "," << p.second+1 << ")";	
}

#define bind(a,b) (((a) << 4) | (b))
static void proc(int& tmp, point tl, point p)
{
	size_t x = tl.first;
	size_t y = tl.second;
	size_t x0 = p.first;
	size_t y0 = p.second;
	
	switch(bind(y0-y,x0-x))
	{
		case bind(1,0): tmp |=  1; break;
		case bind(2,0): tmp |=  8; break;
		case bind(0,1): tmp |=  2; break;
		case bind(1,1): tmp |=  4; break;
		case bind(2,1): tmp |= 32; break;
		case bind(0,2): tmp |= 16; break;
		case bind(1,2): tmp |= 64; break;
		default: break; // ignore all other
	}
	return;
}

static char get_name(shape_num s)
{
	return "NZYSJPABLQCDEFTKIMO"[static_cast<size_t>(s)];
}


shape_num mino::get_shape_num() const
{
	point tl = this->top_left();
	
	shape_num arr[40] = {
		VOID__, B_mino, L_mino, VOID__, VOID__,
		J_mino, D_mino, O_mino, VOID__, M_mino,
		VOID__, C_mino, VOID__, T_mino, VOID__,
		S_mino, VOID__, VOID__, I_mino, P_mino,
		VOID__, VOID__, E_mino, N_mino, VOID__,
		VOID__, VOID__, VOID__, VOID__, Q_mino,
		Y_mino, F_mino, VOID__, VOID__, VOID__,
		VOID__, VOID__, Z_mino, A_mino, K_mino
	}; // scary table
	
	int tmp = 0x00; // bitfield
	proc(tmp, tl, p0);
	proc(tmp, tl, p1);
	proc(tmp, tl, p2);
	proc(tmp, tl, p3);
	return arr[tmp % 40];
}


ostream& operator<<(ostream& o, const mino& m)
{
    return o << "'" << m.ch << "' "
	<< m.p0 << ","
	<< m.p1 << ","
	<< m.p2 << ","
	<< m.p3
	<< "  " << m.get_shape_num()
	<< "  " << get_name(m.get_shape_num());
}
static inline size_t m(size_t a, size_t b){ return a < b ? a : b; }
static inline size_t min(size_t a, size_t b, size_t c, size_t d){ return m(m(a,b),m(c,d)); }

point mino::top_left() const
{
	return point(min(p0.first,p1.first,p2.first,p3.first),min(p0.second,p1.second,p2.second,p3.second));
}
