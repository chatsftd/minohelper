#ifndef MAYBE_H_5d35ecd97713d038e9d8d4bff923d82939949a2c
#define MAYBE_H_5d35ecd97713d038e9d8d4bff923d82939949a2c
#include "debug.h"
template <class T>
class Maybe
{
	bool isJust_;
	T inside;
	Maybe(bool ij, const T& t) : isJust_(ij), inside(t) {}
	Maybe() : isJust_(false), inside() {}
	
public:
	template <class T2> friend Maybe<T2> Nothing() { Maybe<T2> mt; return mt;}
	template <class T2> friend Maybe<T2> Just(const T2& t) { Maybe<T2> mt(true,t); return mt;}
	bool isJust() const{ return this->isJust_; }
	bool isNothing() const{ return !(this->isJust_); }
	T unJust() const;
};

template <class T>
T Maybe<T>::unJust() const
{
	if(this->isJust_)
	{
		return this->inside;
	}
	else
	{
		assert2("cannot unJust Nothing",0);
		T t;
		return t;
	}
}

#endif/*MAYBE_H_5d35ecd97713d038e9d8d4bff923d82939949a2c*/
