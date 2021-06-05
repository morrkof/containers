#include "test.hpp"

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, std::map<Key, T> &src)
{
	os << "std | size = " << src.size() << ", elements: ";
	// for (typename std::list<T>::iterator it = src.begin(); it != src.end(); it++)
	// 	os << *it << " ";
	os << std::endl;
	return os;
}

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, ft::map<Key, T> &src)
{
	os << "ft  | size = " << src.size() << ", elements: ";
	// for (typename ft::list<T>::iterator it = src.begin(); it != src.end(); it++)
	// 	os << *it << " ";
	os << std::endl;
	return os;
}

void test_map()
{
	std::map<int, std::string> s_map;
	ft::map<int, std::string> ft_map;

	s_map.insert(std::make_pair(4, "bla"));
	ft_map.insert(std::make_pair(4, "bla"));

	std::cout << std::endl << s_map << ft_map;
}