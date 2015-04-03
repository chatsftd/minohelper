#ifndef ARGS_H_INCLUDED_483B78994A97B2D564084F52B6E55D47721C1888
#define ARGS_H_INCLUDED_483B78994A97B2D564084F52B6E55D47721C1888
#include <vector>
#include <string>

class arguments2
{
	std::vector<std::string> tokens;
	
public:
	arguments2() : tokens() {}
	void push_back(std::string s) { this->tokens.push_back(s); }
	bool empty() const { return this->tokens.empty(); }
	size_t size() const { return this->tokens.size(); }
	std::string& operator [](size_t n);
	const std::string& operator [](size_t n) const;
	void parse(const std::string& a);
};

#endif/*ARGS_H_INCLUDED_483B78994A97B2D564084F52B6E55D47721C1888*/
