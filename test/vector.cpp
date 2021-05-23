#include "test.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &os, ft::vector<T> &src)
{
	os << "ft  | size = " << src.size() << ", capacity = " << src.capacity() << ", elements: ";
	for (size_t i = 0; i < src.size(); i++)
		os << src[i] << " ";
	os << std::endl;
	return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> &src)
{
	os << "std | size = " << src.size() << ", capacity = " << src.capacity() << ", elements: ";
	for (size_t i = 0; i < src.size(); i++)
		os << src[i] << " ";
	os << std::endl;
	return os;
}

void test_vector()
{
    print_beautiful_title("1. TESTING CONSTRUCTORS:");
	std::vector<std::string> v_empty;
	ft::vector<std::string> ft_empty;
	std::cout << "Empty constructor:" << std::endl << v_empty << ft_empty << std::endl;

	std::vector<int> v_zero(5);
	ft::vector<int> ft_zero(5);
	std::cout << "Fill constructor with default value:" << std::endl << v_zero << ft_zero << std::endl;

    std::vector<int> v_full(3, 42);
	ft::vector<int> ft_full(3, 42);
	std::cout << "Fill constructor (3, 42):" << std::endl  << v_full << ft_full << std::endl;

    std::vector<int> v_range(v_full.begin(), v_full.end()-1);
	ft::vector<int> ft_range(ft_full.begin(), ft_full.end()-1);
	std::cout << "Range constructor (from fill begin - (end-1)):" << std::endl << v_range << ft_range << std::endl;

    std::vector<int> v_copy(v_full);
	ft::vector<int> ft_copy(ft_full);
	std::cout << "Copy constructor (from fill):" << std::endl << v_copy << ft_copy << std::endl;

    print_beautiful_title("2. TESTING ITERATORS:");
    std::vector<int> v_iter;
	ft::vector<int> ft_iter;
    for(int i = 12; i < 20; i++)
    {
        v_iter.push_back(i);
		ft_iter.push_back(i);
    }

    std::cout << "std | Iterating...  ";
    for(std::vector<int>::iterator it = v_iter.begin(); it != v_iter.end(); it++)
        std::cout << *it << "  ";
    std::cout << std::endl;

    std::cout << "ft  | Iterating...  ";
    for(ft::vector<int>::iterator it = ft_iter.begin(); it != ft_iter.end(); it++)
        std::cout << *it << "  ";
    std::cout << std::endl;
	
	std::cout << "std | Reverse iterating...  ";
    for(std::vector<int>::reverse_iterator it = v_iter.rbegin(); it != v_iter.rend(); it++)
        std::cout << *it << "  ";
    std::cout << std::endl;

	std::cout << "ft  | Reverse Iterating...  ";
    for(ft::vector<int>::reverse_iterator it = ft_iter.rbegin(); it != ft_iter.rend(); it++)
        std::cout << *it << "  ";
    std::cout << std::endl;



    print_beautiful_title("3. TESTING CAPACITY:");
    std::cout << std::endl << "............. SIZE && CAPACITY:" << std::endl;
    std::vector<int> v;
	ft::vector<int> ft_v;
    std::cout << "Increasing..." << std::endl;
    for(int i = 0; i != 18; i++)
    {
        std::cout << "std | sz: "  <<  std::setfill(' ') << std::setw(3) << v.size() 
		<< " cpct: " <<  std::setfill(' ') << std::setw(3)  << v.capacity() 
		<< "    ft  | sz: " <<  std::setfill(' ') << std::setw(3) << ft_v.size()
		 << " cpct: " <<  std::setfill(' ') << std::setw(3) << ft_v.capacity() << std::endl;
        v.push_back(42);
		ft_v.push_back(42);
    }
	std::cout << "Decreasing..." << std::endl;
	for(int i = 0; i != 5; i++)
    {
		v.pop_back();
        ft_v.pop_back();
        std::cout << "std | sz: "  <<  std::setfill(' ') << std::setw(3) << v.size() 
		<< " cpct: " <<  std::setfill(' ') << std::setw(3)  << v.capacity() 
		<< "    ft  | sz: " <<  std::setfill(' ') << std::setw(3) << ft_v.size()
		 << " cpct: " <<  std::setfill(' ') << std::setw(3) << ft_v.capacity() << std::endl;
    }

	std::cout << std::endl << "............. RESIZE:" << std::endl;
	std::cout << "Before resize: " << std::endl << v << ft_v;
	v.resize(20, 777);
	ft_v.resize(20, 777);
	std::cout << "After resize to 20: " << std::endl << v << ft_v;
	v.resize(3, 100);
	ft_v.resize(3, 100);
	std::cout << "After resize to 3: " << std::endl << v << ft_v;

	std::cout << std::endl << "............. RESERVE:" << std::endl;
	v.reserve(777);
	ft_v.reserve(777);
	std::cout << "Reserve 777 capacity:" << std::endl << v << ft_v;
	v.reserve(10000);
	ft_v.reserve(10000);
	std::cout << "Reserve 10000 capacity:" << std::endl << v << ft_v;

    std::cout << std::endl << "............. MAX SIZE:" << std::endl;
    std::cout << "std | MAX SIZE is " << v.max_size() << std::endl;
    std::cout << "ft  | MAX SIZE is " << ft_v.max_size() << std::endl;

    std::cout << std::endl << "............. EMPTY:" << std::endl;
    std::vector<int> v_emp;
    ft::vector<int> ft_emp;
    std::cout << "std | IS EMPTY? (-) " << v.empty() << std::endl;
	std::cout << "ft  | IS EMPTY? (-) " << ft_v.empty() << std::endl;
    std::cout << "std | IS EMPTY? (+) " << v_emp.empty() << std::endl; 
    std::cout << "ft  | IS EMPTY? (+) " << ft_emp.empty() << std::endl;



    print_beautiful_title("4. TESTING ELEMENT ACCESS:");
    std::vector<int> v_at;
	ft::vector<int> ft_at;
    for(int i = 42; i < 45; i++)
	{
        v_at.push_back(i);
		ft_at.push_back(i);
	}

    std::cout << std::endl << "............. ACCESS VIA SQUARE BRACKETS:" << std::endl;
    std::cout << "std | elements [0], [1], [2] : " << v_at[0] << " " << v_at[1] << " " << v_at[2] << std::endl;
    std::cout << "ft  | elements [0], [1], [2] : " << ft_at[0] << " " << ft_at[1] << " " << ft_at[2] << std::endl;

    std::cout << std::endl << "............. AT AND THROWING EXCEPTION:" << std::endl;
    std::cout << "std | AT [0] " << v_at.at(0) << std::endl;
	std::cout << "ft  | AT [0] " << ft_at.at(0) << std::endl;
    try 
    {
        std::cout << "std | AT [42] " << v_at.at(42) << std::endl;
    }
    catch(std::out_of_range &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try 
    {
        std::cout << "ft | AT [42] " << ft_at.at(42) << std::endl;
    }
    catch(std::out_of_range &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

	std::cout << std::endl << "............. FRONT && BACK:" << std::endl;
    std::cout << "std | FRONT element: " << v_at.front() << ", BACK element: " << v_at.back() << std::endl;
    std::cout << "ft  | FRONT element: " << ft_at.front() << ", BACK element: " << ft_at.back() << std::endl;



    print_beautiful_title("5. TESTING MODIFIERS:");

	std::vector<int> v_push;
	ft::vector<int> ft_push;

	std::cout << std::endl << "............. PUSH_BACK:" << std::endl;
    for(int i = 42; i < 47; i++)
    {
        v_push.push_back(i);
		ft_push.push_back(i);
        std::cout << "Push_back: added element!" << std::endl << v_push << ft_push; 
    }
   
	std::cout << std::endl << "............. POP_BACK:" << std::endl;
	v_push.pop_back();
	ft_push.pop_back();
	std::cout << "Pop_back: deleted last element, now... " << std::endl << v_push << ft_push;
	v_push.pop_back();
	ft_push.pop_back();
	std::cout << "Pop_back: deleted last element, now... " << std::endl << v_push << ft_push;

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
	v_push.insert(v_push.begin() + 5, 9, 11);
	ft_push.insert(ft_push.begin() + 5, 9, 11);
	std::cout << "Inserting 9 elements '11', now... " << std::endl << v_push << ft_push;

	std::cout << std::endl << "............. INSERT RANGE:" << std::endl;
	std::vector<int> v_pushrange(10);
	ft::vector<int> ft_pushrange(10);
	v_pushrange.insert(v_pushrange.begin(), v_push.begin(), v_push.begin() + 5);
	ft_pushrange.insert(ft_pushrange.begin(), ft_push.begin(), ft_push.begin() + 5);
	std::cout << "Inserting range elements to vector, now... " << std::endl << v_pushrange << ft_pushrange;



	std::cout << std::endl << "............. ERASE SINGLE ELEMENT:" << std::endl;
	{
	std::vector<int> v_erase;
	for(size_t i = 1; i < 10; i++)
		v_erase.push_back(i);
	std::cout << "std | create this:  " << v_erase;
	v_erase.erase(v_erase.begin());
	std::cout << "std | erase first:  " << v_erase;
	v_erase.erase(v_erase.begin() + 5);
	std::cout << "std | erase 7:  " << v_erase;
	}
	{
	ft::vector<int> ft_erase;
	for(size_t i = 1; i < 10; i++)
		ft_erase.push_back(i);
	std::cout << "ft  | create this:  " << ft_erase;
	ft_erase.erase(ft_erase.begin());
	std::cout << "ft  | erase first:  " << ft_erase;
	ft_erase.erase(ft_erase.begin() + 5);
	std::cout << "ft  | erase 7:  " << ft_erase;
	}

	std::cout << std::endl << "............. ERASE MULTIPLY ELEMENTS:" << std::endl;
	{
	std::vector<int> v_erase;
	for(size_t i = 1; i < 10; i++)
		v_erase.push_back(i);
	std::cout << "std | create this:  " << v_erase;
	v_erase.erase(v_erase.begin(), v_erase.begin() + 3);
	std::cout << "std | erase first:  " << v_erase;
	}
	{
	ft::vector<int> ft_erase;
	for(size_t i = 1; i < 10; i++)
		ft_erase.push_back(i);
	std::cout << "ft  | create this:  " << ft_erase;
	ft_erase.erase(ft_erase.begin(), ft_erase.begin() + 3);
	std::cout << "ft  | erase first:  " << ft_erase;
	}


	std::cout << std::endl << "............. ASSIGN:" << std::endl;

	{
		std::vector<int> v_assign;
		for(size_t i = 0; i < 20; i++)
			v_assign.push_back(i);
		std::cout << "std | create this: " << v_assign;
		v_assign.assign(5, 42);
		std::cout << "std | after assign 5/42: " << v_assign;
	}

	{
		ft::vector<int> ft_assign;
		for(size_t i = 0; i < 20; i++)
			ft_assign.push_back(i);
		std::cout << "ft  | create this: " << ft_assign;
		ft_assign.assign(5, 42);
		std::cout << "ft  | after assign 5/42: " << ft_assign;
	}




	std::cout << "IF CAPACITY = 0 ???" << std::endl;
	std::vector<int> v_test;
	std::cout << "created : " << v_test;
	v_test.insert(v_test.begin(), 678);
	std::cout << "now1 : " << v_test;
	v_test.insert(v_test.begin(), 123);
	std::cout << "now2 : " << v_test;
	v_test.insert(v_test.begin(), 45);
	std::cout << "now3 : " << v_test;





	std::cout << std::endl << "CLEAR:" << std::endl;
	v_push.clear();
	ft_push.clear();
	std::cout << "std | after clear: " << v_push;
	std::cout << "ft  | after clear: " << ft_push;



	std::cout << std::endl << "............. SWAP:" << std::endl;

	std::cout << "before swap:" << std::endl <<  "1st - " << v_zero << "2nd - " << v_full
	<<  "1st - " << ft_zero << "2nd - " << ft_full << std::endl ;
	v_zero.swap(v_full);
	ft_zero.swap(ft_full);
	std::cout << "after swap (method):" << std::endl <<  "1st - " << v_zero << "2nd - " << v_full
	<<  "1st - " << ft_zero << "2nd - " << ft_full << std::endl ;

	std::swap(v_zero, v_full);
	ft::swap(ft_zero, ft_full);
	std::cout << "after swap (non-member):" << std::endl <<  "1st - " << ft_zero << "2nd - " << ft_full
	<<  "1st - " << v_zero << "2nd - " << v_full << std::endl ;


    print_beautiful_title("6. TESTING NON-MEMBER OVERLOADS:");
	std::cout << "std | 1 == 2 ? " << (v_zero == v_full) << std::endl;
	std::cout << "ft  | 1 == 2 ? " << (ft_zero == ft_full) << std::endl;
	std::cout << "std | 1 != 2 ? " << (v_zero != v_full) << std::endl;
	std::cout << "ft  | 1 != 2 ? " << (ft_zero != ft_full) << std::endl;
	std::cout << "std | 1 > 2 ? " << (v_zero > v_full) << std::endl;
	std::cout << "ft  | 1 > 2 ? " << (ft_zero > ft_full) << std::endl;
	std::cout << "std | 1 >= 2 ? " << (v_zero >= v_full) << std::endl;
	std::cout << "ft  | 1 >= 2 ? " << (ft_zero >= ft_full) << std::endl;
	std::cout << "std | 1 < 2 ? " << (v_zero < v_full) << std::endl;
	std::cout << "ft  | 1 < 2 ? " << (ft_zero < ft_full) << std::endl;
	std::cout << "std | 1 <= 2 ? " << (v_zero <= v_full) << std::endl;
	std::cout << "ft  | 1 <= 2 ? " << (ft_zero <= ft_full) << std::endl;


	print_beautiful_title("6. TESTING OTHER:");
	std::cout << std::endl << "............. VECTOR OF STRINGS:" << std::endl;
	std::vector<std::string> v_str(5, "kek");
	ft::vector<std::string> ft_str(5, "kek");
	v_str.push_back("cheburek");
	v_str.insert(v_str.begin(), "lol");
	ft_str.push_back("cheburek");
	ft_str.insert(ft_str.begin(), "lol");
	std::cout << v_str << ft_str;

	std::cout << std::endl << "............. VECTOR OF AWESOMENESS:" << std::endl;
	std::vector<Awesome> v_awesome(1, 13);
	ft::vector<Awesome> ft_awesome(1, 13);

	v_awesome.push_back(133);
	ft_awesome.push_back(133);

	std::cout << "std | " << v_awesome[0].getN() << " " << v_awesome[1].getN() << std::endl;
	std::cout << "ft  | " << ft_awesome[0].getN() << " " << ft_awesome[1].getN() << std::endl;
}