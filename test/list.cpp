#include "test.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &os, std::list<T> &src)
{
	os << "std | size = " << src.size() << ", elements: ";
	for (typename std::list<T>::iterator it = src.begin(); it != src.end(); it++)
		os << *it << " ";
	os << std::endl;
	return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, ft::list<T> &src)
{
	os << "ft  | size = " << src.size() << ", elements: ";
	for (typename ft::list<T>::iterator it = src.begin(); it != src.end(); it++)
		os << *it << " ";
	os << std::endl;
	return os;
}

void test_list()
{
	std::cout << "\e[1;32m";
	std::cout << "****************" << std::endl;
	std::cout << "*  🍀 LIST 🍀  *" << std::endl;
	std::cout << "****************" << std::endl;
	std::cout << "\e[0m";

	print_beautiful_title("1. TESTING CONSTRUCTORS:");

	std::list<std::string> v_empty;
	ft::list<std::string> ft_empty;
	std::cout << "Empty constructor:" << std::endl << v_empty << ft_empty << std::endl;

	std::list<int> v_zero(5);
	ft::list<int> ft_zero(5);
	std::cout << "Fill constructor with default value:" << std::endl << v_zero << ft_zero << std::endl;

    std::list<int> v_full(3, 42);
	ft::list<int> ft_full(3, 42);
	std::cout << "Fill constructor (3, 42):" << std::endl  << v_full << ft_full << std::endl;

	std::list<int> v_range(v_full.begin(), v_full.end());
	ft::list<int> ft_range(ft_full.begin(), ft_full.end());
	std::cout << "Range constructor (from fill begin - end):" << std::endl << v_range << ft_range << std::endl;

    // std::list<int> v_copy(v_full);
	// ft::list<int> ft_copy(ft_full);
	// std::cout << "Copy constructor (from fill):" << std::endl << v_copy << ft_copy << std::endl;


	print_beautiful_title("2. TESTING ITERATORS:");
	std::list<int> v_iter;
	ft::list<int> ft_iter;
    for(int i = 10; i < 22; i++)
    {
        v_iter.push_back(i);
		ft_iter.push_back(i);
    }

    std::cout << "std | Iterating...  ";
    for(std::list<int>::iterator it = v_iter.begin(); it != v_iter.end(); it++)
        std::cout << *it << "  ";
    std::cout << std::endl;

    std::cout << "ft  | Iterating...  ";
    for(ft::list<int>::iterator it = ft_iter.begin(); it != ft_iter.end(); it++)
        std::cout << *it << "  ";
    std::cout << std::endl;
	
	std::cout << "std | Reverse iterating...  ";
    for(std::list<int>::reverse_iterator it = v_iter.rbegin(); it != v_iter.rend(); it++)
        std::cout << *it << "  ";
    std::cout << std::endl;

	std::cout << "ft  | Reverse Iterating...  ";
    for(ft::list<int>::reverse_iterator it = ft_iter.rbegin(); it != ft_iter.rend(); it++)
        std::cout << *it << "  ";
    std::cout << std::endl;


	print_beautiful_title("3. TESTING CAPACITY:");
	std::cout << std::endl << "............. SIZE:" << std::endl;
    std::list<int> v;
	ft::list<int> ft_v;
    std::cout << "Increasing..." << std::endl;
    for(int i = 0; i != 18; i++)
    {
        std::cout << "std | sz: "  <<  std::setfill(' ') << std::setw(3) << v.size() 
		<< "    ft  | sz: " <<  std::setfill(' ') << std::setw(3) << ft_v.size() << std::endl;
        v.push_back(42);
		ft_v.push_back(42);
    }
	std::cout << "Decreasing..." << std::endl;
	for(int i = 0; i != 5; i++)
    {
		v.pop_back();
        ft_v.pop_back();
        std::cout << "std | sz: "  <<  std::setfill(' ') << std::setw(3) << v.size() 
		<< "    ft  | sz: " <<  std::setfill(' ') << std::setw(3) << ft_v.size() << std::endl;
    }

	
    std::cout << std::endl << "............. MAX SIZE:" << std::endl;
    std::cout << "std | MAX SIZE is " << v.max_size() << std::endl;
    std::cout << "ft  | MAX SIZE is " << ft_v.max_size() << std::endl;

    std::cout << std::endl << "............. EMPTY:" << std::endl;
    std::list<int> v_emp;
    ft::list<int> ft_emp;
    std::cout << "std | IS EMPTY? (-) " << v.empty() << std::endl;
	std::cout << "ft  | IS EMPTY? (-) " << ft_v.empty() << std::endl;
    std::cout << "std | IS EMPTY? (+) " << v_emp.empty() << std::endl; 
    std::cout << "ft  | IS EMPTY? (+) " << ft_emp.empty() << std::endl;


	print_beautiful_title("4. TESTING ELEMENT ACCESS:");
	std::list<int> v_at;
	ft::list<int> ft_at;
    for(int i = 42; i < 45; i++)
	{
        v_at.push_back(i);
		ft_at.push_back(i);
	}
	std::cout << "std | FRONT element: " << v_at.front() << ", BACK element: " << v_at.back() << std::endl;
    std::cout << "ft  | FRONT element: " << ft_at.front() << ", BACK element: " << ft_at.back() << std::endl;


	print_beautiful_title("5. TESTING MODIFIERS:");
	// assign push_front pop_front push_back pop_back insert erase swap resize clear
	std::cout << std::endl << "............. PUSH_BACK && PUSH_FRONT:" << std::endl;
	std::list<int> s_list;
	ft::list<int> ft_list;
	for (size_t i = 0; i < 15; i++)
	{
		s_list.push_back(i);
		s_list.push_front(i);
		ft_list.push_back(i);
		ft_list.push_front(i);
	}
	std::cout << s_list << ft_list << std::endl;

	std::cout << std::endl << "............. POP_BACK && POP_FRONT:" << std::endl;
	for (size_t i = 0; i < 8; i++)
	{
		s_list.pop_back();
		s_list.pop_front();
		ft_list.pop_back();
		ft_list.pop_front();
	}
	std::cout << s_list << ft_list << std::endl;

	std::list<int> v_push;
	ft::list<int> ft_push;
	std::cout << std::endl << "............. INSERT SINGLE ELEMENT:" << std::endl;
	v_push.insert(v_push.begin(), 666);
	ft_push.insert(ft_push.begin(), 666);
	std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	v_push.insert(v_push.end(), 555);
	ft_push.insert(ft_push.end(), 555);
	std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	v_push.insert(v_push.begin(), 444);
	ft_push.insert(ft_push.begin(), 444);
	std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	v_push.insert(v_push.end(), 333);
	ft_push.insert(ft_push.end(), 333);
	std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	v_push.insert(v_push.begin(), 222);
	ft_push.insert(ft_push.begin(), 222);
	std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	v_push.insert(v_push.end(), 111);
	ft_push.insert(ft_push.end(), 111);
	std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;

	std::cout << std::endl << "............. INSERT MULTIPLY ELEMENTS:" << std::endl;
	v_push.insert(v_push.begin(), 9, 11);
	ft_push.insert(ft_push.begin(), 9, 11);
	std::cout << "Inserting 9 elements '11', now... " << std::endl << v_push << ft_push;

	std::cout << std::endl << "............. INSERT RANGE:" << std::endl;
	std::list<int> v_pushrange(10);
	ft::list<int> ft_pushrange(10);
	v_pushrange.insert(++v_pushrange.begin(), v_push.begin(), v_push.end());
	ft_pushrange.insert(++ft_pushrange.begin(), ft_push.begin(), ft_push.end());
	std::cout << "Inserting range elements to list, now... " << std::endl << v_pushrange << ft_pushrange;


	std::cout << std::endl << "............. ERASE SINGLE ELEMENT:" << std::endl;
	{
	std::list<int> v_erase;
	for(size_t i = 1; i < 10; i++)
		v_erase.push_back(i);
	std::cout << "std | create this:  " << v_erase;
	v_erase.erase(v_erase.begin());
	std::cout << "std | erase first:  " << v_erase;
	v_erase.erase(--v_erase.end());
	std::cout << "std | erase 7:  " << v_erase;
	}
	{
	ft::list<int> ft_erase;
	for(size_t i = 1; i < 10; i++)
		ft_erase.push_back(i);
	std::cout << "ft  | create this:  " << ft_erase;
	ft_erase.erase(ft_erase.begin());
	std::cout << "ft  | erase first:  " << ft_erase;
	ft_erase.erase(--ft_erase.end());
	std::cout << "ft  | erase 7:  " << ft_erase;
	}

	std::cout << std::endl << "............. ERASE MULTIPLY ELEMENTS:" << std::endl;
	{
	std::list<int> v_erase;
	for(size_t i = 1; i < 10; i++)
		v_erase.push_back(i);
	std::cout << "std | create this:  " << v_erase;
	v_erase.erase(++v_erase.begin(), --v_erase.end());
	std::cout << "std | erase first:  " << v_erase;
	}
	{
	ft::list<int> ft_erase;
	for(size_t i = 1; i < 10; i++)
		ft_erase.push_back(i);
	std::cout << "ft  | create this:  " << ft_erase;
	ft_erase.erase(++ft_erase.begin(), --ft_erase.end());
	std::cout << "ft  | erase first:  " << ft_erase;
	}

	std::cout << std::endl << "CLEAR:" << std::endl;
	v_push.clear();
	ft_push.clear();
	std::cout << "std | after clear: " << v_push;
	std::cout << "ft  | after clear: " << ft_push;

	// print_beautiful_title("6. TESTING OPERATIONS:");
	// splice, remove, remove_if, unique, merge, sort, reverse
	// print_beautiful_title("7. TESTING NON-MEMBER OVERLOADS:");

}