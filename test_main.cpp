#include <iostream>
#include "Vector.hpp"

int main()
{
	ft::vector<int> a;
	a.push_back(42);
	a.push_back(43);
	a.push_back(44);

	ft::vector<int> b(a.begin(), a.end());

	for(size_t i = 0; i < b.size(); i++)
	{
		std::cout << b[i] << " | ";
	}
	std::cout << std::endl;
}