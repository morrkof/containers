#include <iostream>
#include <vector>
// #include "Vector.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> &src)
{
	os << "size = " << src.size() << ", capacity = " << src.capacity() << ", elements: ";
	for (size_t i = 0; i < src.size(); i++)
		os << src[i] << " ";
	os << std::endl;
	return os;
}


int main()
{
	std::vector<int> src;
	for(int i = 42; i != 55; i++)
		src.push_back(i);
	std::cout << "source vector: " << src;


	std::vector<int> v1;
	v1.insert(v1.begin(), src.begin(), src.begin()+13);
	std::cout << "1. insert 9 elem to empty vector:  " << v1;

	std::vector<int> v2(7);
	v2.insert(v2.begin(), src.begin(), src.begin()+13);
	std::cout << "2. insert 9 elem to vector(7):  " << v2;

	std::vector<int> v3(7);
	v3.pop_back();
	v3.insert(v3.begin(), src.begin(), src.begin()+13);
	std::cout << "3. insert 9 elem to vector(7) with popback:  " << v3;

}