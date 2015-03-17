#ifndef CONSTRUCT_MINO_H_DEFINED_28957c66eaef03980eb60b8ffdf0b85d11ca0744
#define CONSTRUCT_MINO_H_DEFINED_28957c66eaef03980eb60b8ffdf0b85d11ca0744
#include "type/point.h"
#include <vector>
#include <iostream>



enum shape_num
{
	N_mino = 0, /*   @   @@    @     @@  */
	Z_mino,     /*  @@    @@   @@   @@   */
	Y_mino,     /*  @           @        */
	S_mino,     /*  N     Z     Y    S   */
	
	J_mino,     /*   @   @@   @     @@@  */
	P_mino,     /*   @   @    @@@     @  */
	A_mino,     /*  @@   @               */
	B_mino,     /*   J   P     A     B   */	
	
	L_mino,     /*  @    @@   @@@     @  */
	Q_mino,     /*  @     @   @     @@@  */
	C_mino,     /*  @@    @              */
	D_mino,     /*  L     Q    C     D   */	
	
	E_mino,     /*  @     @   @@@    @   */
	F_mino,     /*  @@   @@    @    @@@  */
	T_mino,     /*  @     @              */
	K_mino,     /*  E     F    T     K   */	
		
	I_mino,     /*  @          @@        */
	M_mino,     /*  @   @@@@   @@        */
	O_mino,     /*  @                    */
	            /*  @                    */	
	            /*  I    M      O        */	
	VOID__ = 0xCCCC
};

class mino
{
private:
	point p0;
	point p1;
	point p2;
	point p3;
	
	
public:
	char ch;
	mino(const std::vector<point>& points, char c);
	friend std::ostream& operator<<(std::ostream& o, const mino& m);
	point top_left() const;
	shape_num get_shape_num() const;
	mino& operator-=(size_t x) 
	{ 
		this->p0 -= x;
		this->p1 -= x;
		this->p2 -= x;
		this->p3 -= x;
		return *this; 
	}
};

inline mino operator-(mino lhs, size_t rhs) { lhs -= rhs; return lhs; }



#endif/*CONSTRUCT_MINO_H_DEFINED_28957c66eaef03980eb60b8ffdf0b85d11ca0744*/
