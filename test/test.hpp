#ifndef TESTHPP
#define TESTHPP

#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <iostream>
#include <iomanip>
#include "../Vector.hpp"
#include "../List.hpp"
// #include "../Map.hpp"
#include "../Stack.hpp"
#include "../Queue.hpp"

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
void test_list(void);
// void test_map(void);
void test_stack(void);
void test_queue(void);

#endif