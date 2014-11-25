#ifndef HEADER_H_DEFINED_2014_10_12_cikbjhewcbqxepjnjpeuiiszzqcse
#define HEADER_H_DEFINED_2014_10_12_cikbjhewcbqxepjnjpeuiiszzqcse 
#include <cassert>
enum status
{
	NO_FILE = -3,
	SOMETHING_WRONG,
	EXIT_ALL,
	ALL_OK
};

template <class T>
class Maybe
{
	bool isJust_;
	T inside;
	Maybe(bool ij, T t) : isJust_(ij), inside(t) {}
	Maybe() : isJust_(false), inside() {}
	
public:
	template <class T2> friend Maybe<T2> Nothing() { Maybe<T2> mt; return mt;}
	template <class T2> friend Maybe<T2> Just(T2 t) { Maybe<T2> mt(true,t); return mt;}
	bool isJust() const{ return this->isJust_; }
	bool isNothing() const{ return !(this->isJust_); }
	T unJust() const
	{
		if(this->isJust_) 
		{
			return this->inside; 
		}
		else
		{
			assert(0);
			T t;
			return t;
		}
	}
};


#endif/*HEADER_H_DEFINED_2014_10_12_cikbjhewcbqxepjnjpeuiiszzqcse*/
