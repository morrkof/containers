#include "test.hpp"

// enable if
template <typename T>
std::ostream &operator<<(std::ostream &os, ft::vector<T> &src)
{
	os << "size = " << src.size() << ", capacity = " << src.capacity() << ", elements: ";
	for (size_t i = 0; i < src.size(); i++)
		os << src[i] << " ";
	os << std::endl;
	return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> &src)
{
	os << "size = " << src.size() << ", capacity = " << src.capacity() << ", elements: ";
	for (size_t i = 0; i < src.size(); i++)
		os << src[i] << " ";
	os << std::endl;
	return os;
}

void test_vector()
{
//     print_beautiful_title("1. TESTING CONSTRUCTORS && DESTRUCTOR:");
//     std::vector<std::string> v_empty;
//     std::cout << "std | Default constructor: size - " << v_empty.size() << ", capacity - " << v_empty.capacity() << std::endl;
//     std::vector<int> v_zero(5);
//     std::cout << "std | Fill constructor with default value: size - " << v_zero.size() << ", capacity - " << v_zero.capacity() 
//     << ", elements: " << v_zero[0] << " " << v_zero[1] << " " << v_zero[2] << " " << v_zero[3] << " " << v_zero[4] << std::endl;
//     std::vector<int> v_full(3, 42);
//     std::cout << "std | Fill constructor with value = 42: size - " << v_full.size() << ", capacity - " << v_full.capacity() 
//     << ", elements: " << v_full[0] << " " << v_full[1] << " " << v_full[2] << std::endl;
//     std::vector<int> v_range(v_full.begin(), v_full.end());
//     std::cout << "std | Range constructor (fill): size - " << v_range.size() << ", capacity - " << v_range.capacity() 
//     << ", elements: " << v_range[0] << " " << v_range[1] << " " << v_range[2] << std::endl;
//     std::vector<int> v_copy(v_full);
//     std::cout << "std | Copy constructor (fill): size - " << v_copy.size() << ", capacity - " << v_copy.capacity() 
//     << ", elements: " << v_copy[0] << " " << v_copy[1] << " " << v_copy[2] << std::endl;

//     ft::vector<std::string> ft_empty;
//     std::cout << "ft  | Default constructor: size - " << ft_empty.size() << ", capacity - " << ft_empty.capacity() << std::endl;
//     std::vector<int> ft_zero(5);
//     std::cout << "ft  | Fill constructor with default value: size - " << ft_zero.size() << ", capacity - " << ft_zero.capacity() 
//     << ", elements: " << ft_zero[0] << " " << ft_zero[1] << " " << ft_zero[2] << " " << ft_zero[3] << " " << ft_zero[4] << std::endl;
//     ft::vector<int> ft_full(3, 42);
//     std::cout << "ft  | Fill constructor with value = 42: size - " << ft_full.size() << ", capacity - " << ft_full.capacity() 
//     << ", elements: " << ft_full[0] << " " << ft_full[1] << " " << ft_full[2] << std::endl;
    
//     // ft::vector<int> ft_range(ft_full.begin(), ft_full.end());
//     // std::cout << "ft | Range constructor (fill): size - " << ft_range.size() << ", capacity - " << ft_range.capacity() 
//     // << ", elements: " << ft_range[0] << " " << ft_range[1] << " " << ft_range[2] << std::endl;
//     // ft::vector<int> ft_copy(ft_full);
//     // std::cout << "ft | Copy constructor (fill): size - " << ft_copy.size() << ", capacity - " << ft_copy.capacity() 
//     // << ", elements: " << ft_copy[0] << " " << ft_copy[1] << " " << ft_copy[2] << std::endl;



//     print_beautiful_title("2. TESTING ITERATORS:");
// // begin, end, rbegin, rend
//     std::vector<int> v_iter;
//     for(int i = 12; i < 20; i++)
//     {
//         v_iter.push_back(i);
//     }
//     std::cout << "std | Iterating...  ";
//     for(std::vector<int>::iterator it = v_iter.begin(); it != v_iter.end(); it++)
//     {
//         std::cout << *it << "  ";
//     }
//     std::cout << std::endl;


//     ft::vector<int> ft_iter;

//     for(int i = 12; i < 20; i++)
//     {
//         ft_iter.push_back(i);
//     }
//     std::cout << "ft  | Iterating...  ";
//     for(ft::vector<int>::iterator it = ft_iter.begin(); it != ft_iter.end(); it++)
//     {
//         std::cout << *it << "  ";
//     }
//     std::cout << std::endl;
	


    print_beautiful_title("3. TESTING CAPACITY:");
    std::cout << "SIZE && CAPACITY:" << std::endl;
    std::vector<int> v;
    std::cout << "std | ++" << std::endl;
    for(int i = 0; i != 18; i++)
    {
        std::cout << "std | SIZE: " << v.size() << " CAPACITY: " << v.capacity() << std::endl;
        v.push_back(42);
    }
	std::cout << "--" << std::endl;
    for(int i = 0; i != 5; i++)
    {
        v.pop_back();
        std::cout << "std | SIZE: " << v.size() << " CAPACITY: " << v.capacity() << std::endl;
    }

    ft::vector<int> ft_v;
    std::cout << "ft  | ++" << std::endl;
    for(int i = 0; i != 18; i++)
    {
        std::cout << "ft  | SIZE: " << ft_v.size() << " CAPACITY: " << ft_v.capacity() << std::endl;
        ft_v.push_back(42);
    }
	std::cout << "--" << std::endl;
	for(int i = 0; i != 5; i++)
    {
        ft_v.pop_back();
        std::cout << "ft  | SIZE: " << ft_v.size() << " CAPACITY: " << ft_v.capacity() << std::endl;
    }

	std::cout << "RESIZE:" << std::endl;
	v.resize(100, 777);
	std::cout << "std | resize: size = " << v.size() << ", capacity = " << v.capacity() << std::endl;
	for(size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	v.resize(3, 100);
	std::cout << "std | resize: size = " << v.size() << ", capacity = " << v.capacity() << std::endl;
	for(size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;

	ft_v.resize(100, 777);
	std::cout << "ft  | resize: size = " << ft_v.size() << ", capacity = " << ft_v.capacity() << std::endl;
	for(size_t i = 0; i < ft_v.size(); i++)
	{
		std::cout << ft_v[i] << " ";
	}
	std::cout << std::endl;
	ft_v.resize(3, 100);
	std::cout << "ft  | resize: size = " << ft_v.size() << ", capacity = " << ft_v.capacity() << std::endl;
	for(size_t i = 0; i < ft_v.size(); i++)
	{
		std::cout << ft_v[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "RESERVE:" << std::endl;
	v.reserve(777);
	std::cout << "std | " << v << std::endl;
	ft_v.reserve(777);
	std::cout << "ft  | " << ft_v  << std::endl;

	v.reserve(10000);
	std::cout << "std | " << v << std::endl;
	ft_v.reserve(10000);
	std::cout << "ft  | " << ft_v  << std::endl;

//     std::cout << "MAX SIZE:" << std::endl;
//     std::cout << "std | MAX SIZE is " << v.max_size() << std::endl;
//     std::cout << "ft  | MAX SIZE is " << ft_v.max_size() << std::endl;
//     std::cout << "EMPTY:" << std::endl;
//     std::vector<int> v_emp;
//     ft::vector<int> ft_emp;
//     std::cout << "std | IS EMPTY? (no) " << v.empty() << std::endl;
//     std::cout << "std | IS EMPTY? (yes) " << v_emp.empty() << std::endl;
//     std::cout << "ft  | IS EMPTY? (no) " << ft_v.empty() << std::endl;
//     std::cout << "ft  | IS EMPTY? (yes) " << ft_emp.empty() << std::endl;



    // print_beautiful_title("4. TESTING ELEMENT ACCESS:");
    // std::vector<int> v_at;
    // for(int i = 42; i < 45; i++)
    //     v_at.push_back(i);
    // ft::vector<int> ft_at;
    // for(int i = 42; i < 45; i++)
    //     ft_at.push_back(i);
    // std::cout << "ACCESS VIA SQUARE BRACKETS:" << std::endl;
    // std::cout << "std | elements: " << v_at[0] << " " << v_at[1] << " " << v_at[2] << std::endl;
    // std::cout << "ft  | elements: " << ft_at[0] << " " << ft_at[1] << " " << ft_at[2] << std::endl;
    // std::cout << "AT AND THROWING EXCEPTION:" << std::endl;
    // std::cout << "std | AT [0] " << v_at.at(0) << std::endl;
    // try 
    // {
    //     std::cout << "std | AT [42] " << v_at.at(42) << std::endl;
    // }
    // catch(std::out_of_range &e)
    // {
    //     std::cerr << "Error: " << e.what() << std::endl;
    // }
    // std::cout << "ft  | AT [0] " << ft_at.at(0) << std::endl;
    // try 
    // {
    //     std::cout << "ft | AT [42] " << ft_at.at(42) << std::endl;
    // }
    // catch(std::out_of_range &e)
    // {
    //     std::cerr << "Error: " << e.what() << std::endl;
    // }
    // std::cout << "std | FRONT element: " << v_at.front() << ", BACK element: " << v_at.back() << std::endl;
    // std::cout << "ft  | FRONT element: " << ft_at.front() << ", BACK element: " << ft_at.back() << std::endl;




    print_beautiful_title("5. TESTING MODIFIERS:");
// assign, push_back+, pop_back+, insert, erase, swap, clear+
    std::cout << "PUSH_BACK:" << std::endl;
    std::vector<int> v_push;
    int j = 0;
    for(int i = 42; i < 45; i++)
    {
        v_push.push_back(i);
        std::cout << "std | Push_back: added element - " << v_push[j] << ", size - " << v_push.size() << ", capacity - " << v_push.capacity() << std::endl;
        j++;
    }
   
    ft::vector<int> ft_push;
    j = 0;
    for(int i = 42; i < 45; i++)
    {
        ft_push.push_back(i);
        std::cout << "ft  | Push_back: added element - " << ft_push[j] << ", size - " << ft_push.size() << ", capacity - " << ft_push.capacity() << std::endl;
        j++;
    }

	std::cout << "POP_BACK:" << std::endl;
	v_push.pop_back();
	ft_push.pop_back();
	std::cout << "std | Pop_back: deleted last element, now size - " << v_push.size() << ", capacity - " << v_push.capacity() << std::endl;
	std::cout << "ft  | Pop_back: deleted last element, now size - " << ft_push.size() << ", capacity - " << ft_push.capacity() << std::endl;

	std::cout << "INSERT:" << std::endl;
	v_push.insert(v_push.begin(), 666);
	v_push.insert(v_push.end(), 555);
	v_push.insert(v_push.begin(), 444);
	// v_push.insert(v_push.begin(), 333);
	// v_push.insert(v_push.begin(), 222);
	// v_push.insert(v_push.begin(), 111);
	// v_push.insert(v_push.begin(), 700);

	std::cout << "std | size = " << v_push.size() << ", capacity = " << v_push.capacity() << ", elements: ";
	for(size_t i = 0; i < v_push.size(); i++)
	{
		std::cout << v_push[i] << " ";
	}
	std::cout << std::endl;

	ft_push.insert(ft_push.begin(), 666);
	ft_push.insert(ft_push.end(), 555);
	ft_push.insert(ft_push.begin(), 444);
	// ft_push.insert(ft_push.begin(), 333);
	// ft_push.insert(ft_push.begin(), 222);
	// ft_push.insert(ft_push.begin(), 111);
	// ft_push.insert(ft_push.begin(), 700);

	std::cout << "ft  | size = " << ft_push.size() << ", capacity = " << ft_push.capacity() << ", elements: ";
	for(size_t i = 0; i < ft_push.size(); i++)
	{
		std::cout << ft_push[i] << " ";
	}
	std::cout << std::endl;		

	// std::cout << "IF CAPACITY = 0 ???" << std::endl;
	// std::vector<int> v_test;
	// std::cout << "created : " << v_test;
	// v_test.insert(v_test.begin(), 678);
	// std::cout << "now1 : " << v_test;
	// v_test.insert(v_test.begin(), 123);
	// std::cout << "now2 : " << v_test;
	// v_test.insert(v_test.begin(), 45);
	// std::cout << "now3 : " << v_test;





	// std::cout << "CLEAR:" << std::endl;
	// v_push.clear();
	// std::cout << "std | after clear: " << v_push;

	// ft_push.clear();
	// std::cout << "ft  | after clear: " << ft_push;

	

    // print_beautiful_title("6. TESTING NON-MEMBER OVERLOADS:");
// swap, ==, !=, <, <=, >, >=,

}