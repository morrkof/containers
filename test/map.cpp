#include "test.hpp"

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, std::map<Key, T> &src)
{
	os << "std | size = " << src.size() << ", elements: ";
	for (typename std::map<Key, T>::iterator it = src.begin(); it != src.end(); ++it)
		os << "[ " << (*it).first << " | " << (*it).second << " ] ";
	os << std::endl;
	return os;
}

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, ft::map<Key, T> &src)
{
	os << "ft  | size = " << src.size() << ", elements: ";
	for (typename ft::map<Key, T>::iterator it = src.begin(); it != src.end(); ++it)
		os << "[ " << (*it).first << " | " <<(*it).second << " ] ";
	os << std::endl;
	return os;
}

void test_map()
{
	std::cout << "\e[1;32m";
	std::cout << "*****************" << std::endl;
	std::cout << "*   🍀 MAP 🍀   *" << std::endl;
	std::cout << "*****************" << std::endl;
	std::cout << "\e[0m";

	print_beautiful_title("1. TESTING CONSTRUCTORS:");
	std::map<int, std::string> s_map;
	ft::map<int, std::string> ft_map;
	std::cout << "Empty constructor:" << std::endl << s_map << ft_map << std::endl;

	s_map.insert(std::make_pair(4, "bla"));
	ft_map.insert(std::make_pair(4, "bla"));

	s_map.insert(std::make_pair(6, "lalala"));
	ft_map.insert(std::make_pair(6, "lalala"));

	s_map.insert(std::make_pair(1, "meow"));
	ft_map.insert(std::make_pair(1, "meow"));

	s_map.insert(std::make_pair(20, "kek"));
	ft_map.insert(std::make_pair(20, "kek"));

	s_map.insert(std::make_pair(-5, "minus five"));
	ft_map.insert(std::make_pair(-5, "minus five"));

	s_map.insert(std::make_pair(3, "three"));
	ft_map.insert(std::make_pair(3, "three"));

	s_map.insert(std::make_pair(5, "five"));
	ft_map.insert(std::make_pair(5, "five"));


	std::map<int, std::string> s_map_range(++s_map.begin(), s_map.end());
	ft::map<int, std::string> ft_map_range(++ft_map.begin(), ft_map.end());
	std::cout << "Range constructor:" << std::endl << s_map_range << ft_map_range << std::endl;

	std::map<int, std::string> s_map_copy(s_map_range);
	ft::map<int, std::string> ft_map_copy(ft_map_range);
	std::cout << "Copy constructor:" << std::endl << s_map_copy << ft_map_copy << std::endl;



	print_beautiful_title("2. TESTING ITERATORS:");
	std::cout << "std | Iterating...  ";
    for (std::map<int, std::string>::iterator it = s_map.begin(); it != s_map.end(); it++)
        std::cout << " [ " << (*it).first << " | " << (*it).second << " ] ";
    std::cout << std::endl;
	std::cout << "ft  | Iterating...  ";
    for (ft::map<int, std::string>::iterator it = ft_map.begin(); it != ft_map.end(); it++)
        std::cout << " [ " << (*it).first << " | " << (*it).second << " ] ";
    std::cout << std::endl;
	
	std::cout << "std | Reverse iterating...  ";
    for (std::map<int, std::string>::reverse_iterator it = s_map.rbegin(); it != s_map.rend(); it++)
        std::cout << " [ " << (*it).first << " | " << (*it).second << " ] ";
    std::cout << std::endl;

	std::cout << "ft  | Reverse Iterating...  ";
    for(ft::map<int, std::string>::reverse_iterator it = ft_map.rbegin(); it != ft_map.rend(); it++)
        std::cout << " [ " << (*it).first << " | " << (*it).second << " ] ";
    std::cout << std::endl;




	print_beautiful_title("3. TESTING CAPACITY:");
	std::cout << std::endl << "............. EMPTY:" << std::endl;
    std::map<int, std::string> s_empty;
	ft::map<int, std::string> ft_empty;
    std::cout << "std | IS EMPTY? (-) " << s_map.empty() << std::endl;
	std::cout << "ft  | IS EMPTY? (-) " << ft_map.empty() << std::endl;
    std::cout << "std | IS EMPTY? (+) " << s_empty.empty() << std::endl; 
    std::cout << "ft  | IS EMPTY? (+) " << ft_empty.empty() << std::endl;
	
	std::cout << std::endl << "............. SIZE:" << std::endl;
	std::cout << "std | SIZE (0) is " << s_empty.size() << std::endl;
    std::cout << "ft  | SIZE (0) is " << ft_empty.size() << std::endl;
    std::cout << "std | SIZE is " << s_map.size() << std::endl;
    std::cout << "ft  | SIZE is " << ft_map.size() << std::endl;

	std::cout << std::endl << "............. MAX SIZE:" << std::endl;
    std::cout << "std | MAX SIZE is " << s_map.max_size() << std::endl;
    std::cout << "ft  | MAX SIZE is " << ft_map.max_size() << std::endl;




	print_beautiful_title("4. TESTING ELEMENT ACCESS:");
	// operator[]




	print_beautiful_title("5. TESTING MODIFIERS:");
	// insert erase swap clear
	std::cout << std::endl << "............. INSERT SINGLE ELEMENT:" << std::endl;
	s_map.insert(std::make_pair(666, "sixsixsix"));
	ft_map.insert(std::make_pair(666, "sixsixsix"));
	s_map.insert(std::make_pair(2, "olala"));
	ft_map.insert(std::make_pair(2, "olala"));
	std::cout << "Insert 2 and 666: " << std::endl << s_map << ft_map;

	std::cout << std::endl << "............. INSERT RANGE:" << std::endl;
	std::map<int, std::string> s_rang;
	ft::map<int, std::string> ft_rang;
	std::map<int, std::string>::iterator s_begin = s_map.find(1);
	ft::map<int, std::string>::iterator ft_begin = ft_map.find(1);
	std::map<int, std::string>::iterator s_end = s_map.find(6);
	ft::map<int, std::string>::iterator ft_end = ft_map.find(6);

	s_rang.insert(s_begin, s_end);
	ft_rang.insert(ft_begin, ft_end);
	std::cout << "Insert range [1 - 6): " << std::endl << s_rang << ft_rang;

	std::cout << std::endl << "............. CLEAR:" << std::endl;
	s_rang.clear();
	ft_rang.clear();
	std::cout << "After clear: " << std::endl << s_rang << ft_rang;


	print_beautiful_title("6. TESTING OBSERVERS:");
	// key_comp value_comp




	print_beautiful_title("7. TESTING OPERATIONS:");
	// find+ count+ lower_bound upper_bound equal_range
	std::cout << std::endl << "............. FIND:" << std::endl;
	std::map<int, std::string>::iterator s_it = s_map.find(1);
	ft::map<int, std::string>::iterator ft_it = ft_map.find(1);
	std::cout << "std | trying to find '1': [ " << (*s_it).first << " | " << (*s_it).second << " ] " << std::endl;
	std::cout << "ft  | trying to find '1': [ " << (*ft_it).first << " | " << (*ft_it).second << " ] " << std::endl;
	s_it = s_map.find(666);
	ft_it = ft_map.find(666);
	std::cout << "std | trying to find '666': [ " << (*s_it).first << " | " << (*s_it).second << " ] " << std::endl;
	std::cout << "ft  | trying to find '666': [ " << (*ft_it).first << " | " << (*ft_it).second << " ] " << std::endl;

	std::cout << std::endl << "............. COUNT:" << std::endl;
	std::cout << "std | check '2' : " << s_map.count(2) << "  , check '88' : " << s_map.count(88) << std::endl;
	std::cout << "ft  | check '2' : " << ft_map.count(2) << "  , check '88' : " << ft_map.count(88) << std::endl;




	print_beautiful_title("8. TESTING NON-MEMBER OVERLOADS:");

	

	


















}