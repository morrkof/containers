#ifndef TESTHPP
#define TESTHPP

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "../Vector.hpp"

class Awesome {
public:
	Awesome(int n): _n(n) {}
	int getN(void) const { return this->_n; }
	bool operator==(Awesome const &rhs) const { return (this->_n == rhs._n); }
	bool operator!=(Awesome const &rhs) const { return (this->_n != rhs._n); }
	bool operator>(Awesome const &rhs) const { return (this->_n > rhs._n); }
	bool operator<(Awesome const &rhs) const { return (this->_n < rhs._n); }
	bool operator>=(Awesome const &rhs) const { return (this->_n >= rhs._n); }
	bool operator<=(Awesome const &rhs) const { return (this->_n <= rhs._n); }
private:
	int _n;
};

std::ostream &operator<<(std::ostream &os, Awesome const &i);
void print_beautiful_title(std::string str);
void test_vector(void);

#endif