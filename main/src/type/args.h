#ifndef ARGS_H_INCLUDED_483B78994A97B2D564084F52B6E55D47721C1888
#define ARGS_H_INCLUDED_483B78994A97B2D564084F52B6E55D47721C1888
#include <vector>
#include <string>

class arguments2
{
	std::vector<std::string> inside;
	
public:
	arguments2() : inside() {}
	void push_back(std::string s){ this->inside.push_back(s); }
	bool empty() const{ return this->inside.empty(); }
	size_t size() const{ return this->inside.size(); }
	std::string& operator [](size_t n);
	std::string operator [](size_t n) const;
	void parse(const std::string& a);
};

#endif/*ARGS_H_INCLUDED_483B78994A97B2D564084F52B6E55D47721C1888*/
