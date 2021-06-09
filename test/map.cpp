#include "test.hpp"

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, std::map<Key, T> &src)
{
	os << "std | size = " << src.size() << ", elements: ";
	for (typename std::map<Key, T>::iterator it = src.begin(); it != src.end(); ++it)
		os << "[" << (*it).first << " : " << (*it).second << "] ";
	os << std::endl;
	return os;
}

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, ft::map<Key, T> &src)
{
	os << "ft  | size = " << src.size() << ", elements: ";
	for (typename ft::map<Key, T>::iterator it = src.begin(); it != src.end(); ++it)
		os << "[" << (*it).first << " : " <<(*it).second << "] ";
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

	s_map.insert(std::make_pair(24, "twenty-four"));
	ft_map.insert(std::make_pair(24, "twenty-four"));

	s_map.insert(std::make_pair(5, "five"));
	ft_map.insert(std::make_pair(5, "five"));

	s_map.insert(std::make_pair(1, "one"));
	ft_map.insert(std::make_pair(1, "one"));

	s_map.insert(std::make_pair(15, "pyatnadcat"));
	ft_map.insert(std::make_pair(15, "pyatnadcat"));

	s_map.insert(std::make_pair(3, "trois"));
	ft_map.insert(std::make_pair(3, "trois"));

	s_map.insert(std::make_pair(8, "eight"));
	ft_map.insert(std::make_pair(8, "eight"));

	s_map.insert(std::make_pair(-5, "minus five"));
	ft_map.insert(std::make_pair(-5, "minus five"));

	s_map.insert(std::make_pair(100, "cent"));
	ft_map.insert(std::make_pair(100, "cent"));

	s_map.insert(std::make_pair(4, "quatre"));
	ft_map.insert(std::make_pair(4, "quatre"));

	std::map<int, std::string> s_map_range(++s_map.begin(), s_map.end());
	ft::map<int, std::string> ft_map_range(++ft_map.begin(), ft_map.end());
	std::cout << "Range constructor:" << std::endl << s_map_range << ft_map_range << std::endl;

	std::map<int, std::string> s_map_copy(s_map_range);
	ft::map<int, std::string> ft_map_copy(ft_map_range);
	std::cout << "Copy constructor:" << std::endl << s_map_copy << ft_map_copy << std::endl;


	print_beautiful_title("2. TESTING ITERATORS:");
	std::cout << "std | Iterating...  ";
    for (std::map<int, std::string>::iterator it = s_map.begin(); it != s_map.end(); it++)
        std::cout << " [" << (*it).first << " : " << (*it).second << "] ";
    std::cout << std::endl;
	std::cout << "ft  | Iterating...  ";
    for (ft::map<int, std::string>::iterator it = ft_map.begin(); it != ft_map.end(); it++)
        std::cout << " [" << (*it).first << " : " << (*it).second << "] ";
    std::cout << std::endl;
	
	std::cout << "std | Reverse iterating...  ";
    for (std::map<int, std::string>::reverse_iterator it = s_map.rbegin(); it != s_map.rend(); it++)
        std::cout << " [" << (*it).first << " : " << (*it).second << "] ";
    std::cout << std::endl;

	std::cout << "ft  | Reverse Iterating...  ";
    for(ft::map<int, std::string>::reverse_iterator it = ft_map.rbegin(); it != ft_map.rend(); it++)
        std::cout << " [" << (*it).first << " : " << (*it).second << "] ";
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
	std::cout << std::endl << "............. OPERATOR []:" << std::endl;
	std::cout << "Value of [5]:  std - " << s_map[5] << "  | ft - " << ft_map[5] << std::endl;
	std::cout << "Value of [10]:  std - " << s_map[10] << "  | ft - " << ft_map[10] << std::endl;


	print_beautiful_title("5. TESTING MODIFIERS:");

	std::cout << std::endl << "............. INSERT SINGLE ELEMENT:" << std::endl;
	s_map.insert(std::make_pair(666, "sixsixsix"));
	ft_map.insert(std::make_pair(666, "sixsixsix"));
	s_map.insert(std::make_pair(2, "olala"));
	ft_map.insert(std::make_pair(2, "olala"));
	std::cout << "Insert 2 and 666: " << std::endl << s_map << ft_map;

	std::cout << std::endl << "............. INSERT SINGLE ELEMENT BY POSITION:" << std::endl;

	std::map<int, std::string>::iterator s_pos = s_map.find(10);
	ft::map<int, std::string>::iterator ft_pos = ft_map.find(10);
	s_map.insert(s_pos, std::make_pair(11, "six"));
	ft_map.insert(ft_pos, std::make_pair(11, "six"));
	std::cout << "Insert 6: " << std::endl << s_map << ft_map;


	std::cout << std::endl << "............. INSERT RANGE:" << std::endl;
	std::map<int, std::string> s_rang;
	ft::map<int, std::string> ft_rang;
	std::map<int, std::string>::iterator s_begin = s_map.find(1);
	ft::map<int, std::string>::iterator ft_begin = ft_map.find(1);
	std::map<int, std::string>::iterator s_end = s_map.find(5);
	ft::map<int, std::string>::iterator ft_end = ft_map.find(5);

	s_rang.insert(s_begin, s_end);
	ft_rang.insert(ft_begin, ft_end);
	std::cout << "Insert range [1 - 5): " << std::endl << s_rang << ft_rang;

	std::cout << std::endl << "............. ERASE SINGLE ELEMENT BY KEY:" << std::endl;
	std::cout << "erase nonexistent element (-200)  std - " << s_map.erase(-200) << "  ft - " << ft_map.erase(-200) << std::endl;
	s_map.erase(s_map.find(3));
	ft_map.erase(ft_map.find(3));
	s_map.erase(s_map.find(4));
	ft_map.erase(ft_map.find(4));
	std::cout << "erase 3 and 4: " << std::endl << s_map << ft_map << std::endl;


	std::cout << std::endl << "............. ERASE SINGLE ELEMENT BY ITERATOR:" << std::endl;

	s_map.erase(s_map.find(5));
	ft_map.erase(ft_map.find(5));
	std::cout << "erase 5: " << std::endl << s_map << ft_map << std::endl;
	s_map.erase(s_map.find(8));
	ft_map.erase(ft_map.find(8));
	std::cout << "erase 8: " << std::endl << s_map << ft_map << std::endl;

	std::cout << std::endl << "............. ERASE RANGE:" << std::endl;

	s_map.erase(s_map.find(10), s_map.find(24));
	ft_map.erase(ft_map.find(10), ft_map.find(24));
	std::cout << "erase range " << std::endl << s_map << ft_map << std::endl;

	
	std::cout << std::endl << "............. SWAP:" << std::endl;

	std::cout << "before swap:" << std::endl <<  "1st - " << s_map << "2nd - " << s_rang
	<<  "1st - " << ft_map << "2nd - " << ft_rang << std::endl ;
	s_map.swap(s_rang);
	ft_map.swap(ft_rang);
	std::cout << "after swap (method):" << std::endl <<  "1st - " << s_map << "2nd - " << s_rang
	<<  "1st - " << ft_map << "2nd - " << ft_rang << std::endl ;
	std::swap(s_map, s_rang);
	ft::swap(ft_map, ft_rang);
	std::cout << "after swap (non-member):" << std::endl <<  "1st - " << s_map << "2nd - " << s_rang
	<<  "1st - " << ft_map << "2nd - " << ft_rang << std::endl ;

	std::cout << std::endl << "............. CLEAR:" << std::endl;
	s_rang.clear();
	ft_rang.clear();
	std::cout << "After clear: " << std::endl << s_rang << ft_rang;




	print_beautiful_title("6. TESTING OBSERVERS:");

	{
		std::cout << "............. KEY_COMP:" << std::endl;
		std::map<char,int> mymap;
		ft::map<char,int> ft_mymap;
		std::map<char,int>::key_compare mycomp = mymap.key_comp();
		ft::map<char,int>::key_compare ft_mycomp = ft_mymap.key_comp();

		mymap['a']=100;
		mymap['b']=200;
		mymap['c']=300;
		ft_mymap['a']=100;
		ft_mymap['b']=200;
		ft_mymap['c']=300;

		char highest = mymap.rbegin()->first;     // key value of last element
		char ft_highest = (*(ft_mymap.rbegin())).first;
		mymap['d']=400;
		ft_mymap['d']=400;
		std::cout << "std :" << std::endl;
		std::map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( mycomp((*it++).first, highest) );

		std::cout << "ft  :" << std::endl;
		ft::map<char,int>::iterator ft_it = ft_mymap.begin();
		do {
			std::cout << (*ft_it).first << " => " << (*ft_it).second << '\n';
		} while ( ft_mycomp((*ft_it++).first, ft_highest) );

		std::cout << '\n';
	}

	{
		std::cout << "............. VALUE_COMP:" << std::endl;


		std::map<char,int> mymap;
		ft::map<char,int> ft_mymap;

		mymap['x']=1001;
		mymap['y']=2002;
		mymap['z']=3003;
		ft_mymap['x']=1001;
		ft_mymap['y']=2002;
		ft_mymap['z']=3003;

		std::pair<char,int> highest = *(mymap.rbegin());          // last element
		std::pair<char,int> ft_highest = *(ft_mymap.rbegin());

		std::map<char,int>::iterator it = mymap.begin();
		ft::map<char,int>::iterator ft_it = ft_mymap.begin();
		std::cout << "std :" << std::endl;
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( mymap.value_comp()(*it++, highest) );

		std::cout << "ft  :" << std::endl;
			do {
			std::cout << (*ft_it).first << " => " << (*ft_it).second << '\n';
		} while ( ft_mymap.value_comp()(*ft_it++, ft_highest) );
	}




	print_beautiful_title("7. TESTING OPERATIONS:");

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

	std::cout << std::endl << "............. UPPER_BOUND && LOWER_BOUND:" << std::endl;
	{
		std::map<char,int> mymap;
		std::map<char,int>::iterator itlow,itup;
		std::map<char,int> mymap_new;
		ft::map<char,int> ft_mymap;
		ft::map<char,int>::iterator ft_itlow,ft_itup;
		ft::map<char,int> ft_mymap_new;

		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;
		ft_mymap['a']=20;
		ft_mymap['b']=40;
		ft_mymap['c']=60;
		ft_mymap['d']=80;
		ft_mymap['e']=100;

		itlow=mymap.lower_bound ('b');  // itlow points to b
		itup=mymap.upper_bound ('d');   // itup points to e (not d!)
		ft_itlow=ft_mymap.lower_bound ('b');  // ft_itlow points to b
		ft_itup=ft_mymap.upper_bound ('d');   // ft_itup points to e (not d!)

		mymap_new.insert(itlow,itup);
		ft_mymap_new.insert(ft_itlow,ft_itup);
		std::cout << "std:\n";
		for (std::map<char,int>::iterator it=mymap_new.begin(); it!=mymap_new.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "ft:\n";
		for (ft::map<char,int>::iterator it=ft_mymap_new.begin(); it!=ft_mymap_new.end(); ++it)
			std::cout << (*(it)).first << " => " << (*(it)).second << '\n';
	}

	std::cout << std::endl << "............. EQUAL_RANGE:" << std::endl;
	{
		std::map<char,int> mymap;
		ft::map<char,int> ft_mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		ft_mymap['a']=10;
		ft_mymap['b']=20;
		ft_mymap['c']=30;

		std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
		ret = mymap.equal_range('b');
		std::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ft_ret;
		ft_ret = ft_mymap.equal_range('b');
		std::cout << "std:\n";
		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';
		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';

		std::cout << "ft:\n";
		std::cout << "lower bound points to: ";
		std::cout << (*(ft_ret.first)).first << " => " << (*(ft_ret.first)).second << '\n';
		std::cout << "upper bound points to: ";
		std::cout << (*(ft_ret.second)).first << " => " << (*(ft_ret.second)).second << '\n';
	}

	

	


















}