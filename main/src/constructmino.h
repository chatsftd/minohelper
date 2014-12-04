#ifndef CONSTRUCT_MINO_H_DEFINED_28957c66eaef03980eb60b8ffdf0b85d11ca0744
#define CONSTRUCT_MINO_H_DEFINED_28957c66eaef03980eb60b8ffdf0b85d11ca0744
#include <vector>
#include <iostream>


#define WRONG_PLACE (0xCCCCCCCC)
struct point
{
	size_t first;
	size_t second;
	point(size_t f, size_t s) : first(f), second(s) {}
	point() : first(WRONG_PLACE), second(WRONG_PLACE) {}
	friend std::ostream& operator<<(std::ostream& o, const point& p);
};

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
	char ch;
	
public:
	mino(const std::vector<point>& points, char c);
	friend std::ostream& operator<<(std::ostream& o, const mino& m);
	point top_left() const;
	shape_num get_shape_num() const;

};




#endif/*CONSTRUCT_MINO_H_DEFINED_28957c66eaef03980eb60b8ffdf0b85d11ca0744*/
