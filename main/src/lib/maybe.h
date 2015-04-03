#ifndef MAYBE_H_5d35ecd97713d038e9d8d4bff923d82939949a2c
#define MAYBE_H_5d35ecd97713d038e9d8d4bff923d82939949a2c
#include "debug.h"
template <class T>
class Maybe
{
	bool isJust_;
	T t;
	Maybe(bool ij, const T& t_) : isJust_(ij), t(t_) {}
	
public:
	Maybe() : isJust_(false), t() {}
	template <class T2> friend Maybe<T2> Nothing() { Maybe<T2> mt; return mt;}
	template <class T2> friend Maybe<T2> Just(const T2& t_) { Maybe<T2> mt(true,t_); return mt;}
	bool isJust() const { return this->isJust_; }
	bool isNothing() const { return !(this->isJust_); }
	T unJust() const;
};

template <class T>
T Maybe<T>::unJust() const
{
	if(this->isJust_) {
		return this->t;
	} else {
		assert2("cannot unJust Nothing",0);
		T t_;
		return t_;
	}
}

#endif/*MAYBE_H_5d35ecd97713d038e9d8d4bff923d82939949a2c*/
