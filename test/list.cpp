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

bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

bool single_digit (const unsigned int& value) { return (value<10); }

bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

void test_list()
{
	std::cout << "\e[1;32m";
	std::cout << "****************" << std::endl;
	std::cout << "*  🍀 LIST 🍀  *" << std::endl;
	std::cout << "****************" << std::endl;
	std::cout << "\e[0m";

	// print_beautiful_title("1. TESTING CONSTRUCTORS:");

	// std::list<std::string> v_empty;
	// ft::list<std::string> ft_empty;
	// std::cout << "Empty constructor:" << std::endl << v_empty << ft_empty << std::endl;

	// std::list<int> v_zero(5);
	// ft::list<int> ft_zero(5);
	// std::cout << "Fill constructor with default value:" << std::endl << v_zero << ft_zero << std::endl;

    // std::list<int> v_full(3, 42);
	// ft::list<int> ft_full(3, 42);
	// std::cout << "Fill constructor (3, 42):" << std::endl  << v_full << ft_full << std::endl;

	// std::list<int> v_range(v_full.begin(), v_full.end());
	// ft::list<int> ft_range(ft_full.begin(), ft_full.end());
	// std::cout << "Range constructor (from fill begin - end):" << std::endl << v_range << ft_range << std::endl;

    // std::list<int> v_copy(v_full);
	// ft::list<int> ft_copy(ft_full);
	// std::cout << "Copy constructor (from fill):" << std::endl << v_copy << ft_copy << std::endl;


	// print_beautiful_title("2. TESTING ITERATORS:");
	// std::list<int> v_iter;
	// ft::list<int> ft_iter;
    // for(int i = 10; i < 22; i++)
    // {
    //     v_iter.push_back(i);
	// 	ft_iter.push_back(i);
    // }

    // std::cout << "std | Iterating...  ";
    // for(std::list<int>::iterator it = v_iter.begin(); it != v_iter.end(); it++)
    //     std::cout << *it << "  ";
    // std::cout << std::endl;

    // std::cout << "ft  | Iterating...  ";
    // for(ft::list<int>::iterator it = ft_iter.begin(); it != ft_iter.end(); it++)
    //     std::cout << *it << "  ";
    // std::cout << std::endl;
	
	// std::cout << "std | Reverse iterating...  ";
    // for(std::list<int>::reverse_iterator it = v_iter.rbegin(); it != v_iter.rend(); it++)
    //     std::cout << *it << "  ";
    // std::cout << std::endl;

	// std::cout << "ft  | Reverse Iterating...  ";
    // for(ft::list<int>::reverse_iterator it = ft_iter.rbegin(); it != ft_iter.rend(); it++)
    //     std::cout << *it << "  ";
    // std::cout << std::endl;


	// print_beautiful_title("3. TESTING CAPACITY:");
	// std::cout << std::endl << "............. SIZE:" << std::endl;
    // std::list<int> v;
	// ft::list<int> ft_v;
    // std::cout << "Increasing..." << std::endl;
    // for(int i = 0; i != 18; i++)
    // {
    //     std::cout << "std | sz: "  <<  std::setfill(' ') << std::setw(3) << v.size() 
	// 	<< "    ft  | sz: " <<  std::setfill(' ') << std::setw(3) << ft_v.size() << std::endl;
    //     v.push_back(42);
	// 	ft_v.push_back(42);
    // }
	// std::cout << "Decreasing..." << std::endl;
	// for(int i = 0; i != 5; i++)
    // {
	// 	v.pop_back();
    //     ft_v.pop_back();
    //     std::cout << "std | sz: "  <<  std::setfill(' ') << std::setw(3) << v.size() 
	// 	<< "    ft  | sz: " <<  std::setfill(' ') << std::setw(3) << ft_v.size() << std::endl;
    // }

	
    // std::cout << std::endl << "............. MAX SIZE:" << std::endl;
    // std::cout << "std | MAX SIZE is " << v.max_size() << std::endl;
    // std::cout << "ft  | MAX SIZE is " << ft_v.max_size() << std::endl;

    // std::cout << std::endl << "............. EMPTY:" << std::endl;
    // std::list<int> v_emp;
    // ft::list<int> ft_emp;
    // std::cout << "std | IS EMPTY? (-) " << v.empty() << std::endl;
	// std::cout << "ft  | IS EMPTY? (-) " << ft_v.empty() << std::endl;
    // std::cout << "std | IS EMPTY? (+) " << v_emp.empty() << std::endl; 
    // std::cout << "ft  | IS EMPTY? (+) " << ft_emp.empty() << std::endl;


	// print_beautiful_title("4. TESTING ELEMENT ACCESS:");
	// std::list<int> v_at;
	// ft::list<int> ft_at;
    // for(int i = 42; i < 45; i++)
	// {
    //     v_at.push_back(i);
	// 	ft_at.push_back(i);
	// }
	// std::cout << "std | FRONT element: " << v_at.front() << ", BACK element: " << v_at.back() << std::endl;
    // std::cout << "ft  | FRONT element: " << ft_at.front() << ", BACK element: " << ft_at.back() << std::endl;


	// print_beautiful_title("5. TESTING MODIFIERS:");
	// // assign push_front pop_front push_back pop_back insert erase swap resize clear
	// std::cout << std::endl << "............. PUSH_BACK && PUSH_FRONT:" << std::endl;
	// std::list<int> s_list;
	// ft::list<int> ft_list;
	// for (size_t i = 0; i < 15; i++)
	// {
	// 	s_list.push_back(i);
	// 	s_list.push_front(i);
	// 	ft_list.push_back(i);
	// 	ft_list.push_front(i);
	// }
	// std::cout << s_list << ft_list << std::endl;

	// std::cout << std::endl << "............. POP_BACK && POP_FRONT:" << std::endl;
	// for (size_t i = 0; i < 8; i++)
	// {
	// 	s_list.pop_back();
	// 	s_list.pop_front();
	// 	ft_list.pop_back();
	// 	ft_list.pop_front();
	// }
	// std::cout << s_list << ft_list << std::endl;

	// std::list<int> v_push;
	// ft::list<int> ft_push;
	// std::cout << std::endl << "............. INSERT SINGLE ELEMENT:" << std::endl;
	// v_push.insert(v_push.begin(), 666);
	// ft_push.insert(ft_push.begin(), 666);
	// std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	// v_push.insert(v_push.end(), 555);
	// ft_push.insert(ft_push.end(), 555);
	// std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	// v_push.insert(v_push.begin(), 444);
	// ft_push.insert(ft_push.begin(), 444);
	// std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	// v_push.insert(v_push.end(), 333);
	// ft_push.insert(ft_push.end(), 333);
	// std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	// v_push.insert(v_push.begin(), 222);
	// ft_push.insert(ft_push.begin(), 222);
	// std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;
	// v_push.insert(v_push.end(), 111);
	// ft_push.insert(ft_push.end(), 111);
	// std::cout << "Inserting element, now... " << std::endl << v_push << ft_push;

	// std::cout << std::endl << "............. INSERT MULTIPLY ELEMENTS:" << std::endl;
	// v_push.insert(v_push.begin(), 9, 11);
	// ft_push.insert(ft_push.begin(), 9, 11);
	// std::cout << "Inserting 9 elements '11', now... " << std::endl << v_push << ft_push;

	// std::cout << std::endl << "............. INSERT RANGE:" << std::endl;
	// std::list<int> v_pushrange(10);
	// ft::list<int> ft_pushrange(10);
	// v_pushrange.insert(++v_pushrange.begin(), v_push.begin(), v_push.end());
	// ft_pushrange.insert(++ft_pushrange.begin(), ft_push.begin(), ft_push.end());
	// std::cout << "Inserting range elements to list, now... " << std::endl << v_pushrange << ft_pushrange;


	// std::cout << std::endl << "............. ERASE SINGLE ELEMENT:" << std::endl;
	// {
	// std::list<int> v_erase;
	// for(size_t i = 1; i < 10; i++)
	// 	v_erase.push_back(i);
	// std::cout << "std | create this:  " << v_erase;
	// v_erase.erase(v_erase.begin());
	// std::cout << "std | erase first:  " << v_erase;
	// v_erase.erase(--v_erase.end());
	// std::cout << "std | erase 7:  " << v_erase;
	// }
	// {
	// ft::list<int> ft_erase;
	// for(size_t i = 1; i < 10; i++)
	// 	ft_erase.push_back(i);
	// std::cout << "ft  | create this:  " << ft_erase;
	// ft_erase.erase(ft_erase.begin());
	// std::cout << "ft  | erase first:  " << ft_erase;
	// ft_erase.erase(--ft_erase.end());
	// std::cout << "ft  | erase 7:  " << ft_erase;
	// }

	// std::cout << std::endl << "............. ERASE MULTIPLY ELEMENTS:" << std::endl;
	// {
	// std::list<int> v_erase;
	// for(size_t i = 1; i < 10; i++)
	// 	v_erase.push_back(i);
	// std::cout << "std | create this:  " << v_erase;
	// v_erase.erase(++v_erase.begin(), --v_erase.end());
	// std::cout << "std | erase first:  " << v_erase;
	// }
	// {
	// ft::list<int> ft_erase;
	// for(size_t i = 1; i < 10; i++)
	// 	ft_erase.push_back(i);
	// std::cout << "ft  | create this:  " << ft_erase;
	// ft_erase.erase(++ft_erase.begin(), --ft_erase.end());
	// std::cout << "ft  | erase first:  " << ft_erase;
	// }
	// {
	// std::list<int> v_erase;
	// ft::list<int> ft_erase;
	// for(size_t i = 1; i < 10; i++)
	// {
	// 	v_erase.push_back(i);
	// 	ft_erase.push_back(i);
	// }
	// std::cout << std::endl << "............. RESIZE:" << std::endl;
	// std::cout << "Before resize: " << std::endl << v_erase << ft_erase;
	// v_erase.resize(20, 777);
	// ft_erase.resize(20, 777);
	// std::cout << "After resize to 20: " << std::endl << v_erase << ft_erase;
	// v_erase.resize(3, 100);
	// ft_erase.resize(3, 100);
	// std::cout << "After resize to 3: " << std::endl << v_erase << ft_erase;
	// }


	// std::cout << std::endl << "CLEAR:" << std::endl;
	// v_push.clear();
	// ft_push.clear();
	// std::cout << "std | after clear: " << v_push;
	// std::cout << "ft  | after clear: " << ft_push;

	print_beautiful_title("6. TESTING OPERATIONS:");
	// splice, remove, remove_if, unique, merge, sort, reverse

	std::list<int> std_spl;
	std::list<int> std_spl2;
	ft::list<int> ft_spl;
	ft::list<int> ft_spl2;

	for(size_t i = 5; i != 9; i++)
	{
		std_spl.push_back(i);
		ft_spl.push_back(i);
	}

	for(size_t i = 42; i != 45; i++)
	{
		std_spl2.push_back(i);
		ft_spl2.push_back(i);
	}

	std_spl.splice(++std_spl.begin(), std_spl2);
	ft_spl.splice(++ft_spl.begin(), ft_spl2);
	std::cout << "Splice: " << std::endl << std_spl << ft_spl;
	std::cout << "---2nd list after splice: " << std::endl << std_spl2 << ft_spl2;
	for(size_t i = 777; i != 782; i++)
	{
		std_spl2.push_back(i);
		ft_spl2.push_back(i);
	}
	std_spl.splice(--std_spl.end(), std_spl2);
	ft_spl.splice(--ft_spl.end(), ft_spl2);
	std::cout << "Splice: " << std::endl << std_spl << ft_spl;
	std::cout << "---2nd list after splice: " << std::endl << std_spl2 << ft_spl2;

	for(size_t i = 13; i != 19; i++)
	{
		std_spl2.push_back(i);
		ft_spl2.push_back(i);
	}

	std_spl.splice(++std_spl.begin(), std_spl2, --std_spl2.end());
	ft_spl.splice(++ft_spl.begin(), ft_spl2, --ft_spl2.end());
	std::cout << "Splice (1 elem): " << std::endl << std_spl << ft_spl;
	std::cout << "---2nd list after splice: " << std::endl << std_spl2 << ft_spl2;

	std_spl.splice(--std_spl.end(), std_spl2, ++std_spl2.begin(), --std_spl2.end());
	ft_spl.splice(--ft_spl.end(), ft_spl2, ++ft_spl2.begin(), --ft_spl2.end());
	std::cout << "Splice (range elem): " << std::endl << std_spl << ft_spl;
	std::cout << "---2nd list after splice: " << std::endl << std_spl2 << ft_spl2;

	std::list<int> std_rem(5, 777);
	ft::list<int> ft_rem(5, 777);

	for(size_t i = 775; i != 780; i++)
	{
		std_rem.push_back(i);
		std_rem.push_front(i);
		ft_rem.push_back(i);
		ft_rem.push_front(i);
	}
	std::cout << "Before remove: " << std::endl << std_rem << ft_rem;
	std_rem.remove(777);
	ft_rem.remove(777);
	std::cout << "After remove: " << std::endl << std_rem << ft_rem;


	std_rem.sort();
	ft_rem.sort();
	std::cout << "After sort: " << std::endl << std_rem << ft_rem;

	std::list<std::string> std_sort_cmp;
	ft::list<std::string> ft_sort_cmp;

	std_sort_cmp.push_back("Hello");
	std_sort_cmp.push_back("privet");
	std_sort_cmp.push_back("Aaaa");
	std_sort_cmp.push_back("world");
	std_sort_cmp.push_back("begemot");
	std_sort_cmp.push_back("Brrr");
	ft_sort_cmp.push_back("Hello");
	ft_sort_cmp.push_back("privet");
	ft_sort_cmp.push_back("Aaaa");
	ft_sort_cmp.push_back("world");
	ft_sort_cmp.push_back("begemot");
	ft_sort_cmp.push_back("Brrr");

	std::cout << "Before compare sort: " << std::endl << std_sort_cmp << ft_sort_cmp;
	std_sort_cmp.sort(compare_nocase);
	ft_sort_cmp.sort(compare_nocase);
	std::cout << "After compare sort: " << std::endl << std_sort_cmp << ft_sort_cmp;

	std_sort_cmp.reverse();
	ft_sort_cmp.reverse();
	std::cout << "After reverse: " << std::endl << std_sort_cmp << ft_sort_cmp;

	std::list<int> std_remove_if;
	ft::list<int> ft_remove_if;
	for(size_t i = 6; i != 13; i++)
	{
		std_remove_if.push_back(i);
		std_remove_if.push_front(i);
		ft_remove_if.push_back(i);
		ft_remove_if.push_front(i);
	}
	std::cout << "Before remove_if: " << std::endl << std_remove_if << ft_remove_if;
	std_remove_if.remove_if(single_digit);
	ft_remove_if.remove_if(single_digit);
	std::cout << "After remove_if: " << std::endl << std_remove_if << ft_remove_if;

	std::list<int> std_uniq(4, 10);
	ft::list<int> ft_uniq(4, 10);
	for(size_t i = 6; i != 13; i++)
	{
		std_uniq.push_back(i);
		std_uniq.push_front(i);
		ft_uniq.push_back(i);
		ft_uniq.push_front(i);
	}
	std_uniq.sort();
	ft_uniq.sort();
	std::cout << "Before unique: " << std::endl << std_uniq << ft_uniq;
	std_uniq.unique();
	ft_uniq.unique();
	std::cout << "After unique: " << std::endl << std_uniq << ft_uniq;

	std::list<double> std_uniq_if;
	ft::list<double> ft_uniq_if;
	for(double i = 3.3; i < 13; i+=0.4)
	{
		std_uniq_if.push_back(i);
		ft_uniq_if.push_back(i);
	}
	std_uniq_if.sort();
	ft_uniq_if.sort();
	std::cout << "Before unique: " << std::endl << std_uniq_if << ft_uniq_if;
	std_uniq_if.unique(same_integral_part);
	ft_uniq_if.unique(same_integral_part);
	std::cout << "After unique: " << std::endl << std_uniq_if << ft_uniq_if;

	{
	std::list<int> std_merge(3, 7);
	ft::list<int> ft_merge(3, 7);
	std::list<int> std_merge2(2, 5);
	ft::list<int> ft_merge2(2, 5);
	for(size_t i = 6; i != 13; i++)
	{
		std_merge.push_back(i);
		std_merge.push_front(i);
		ft_merge.push_back(i);
		ft_merge.push_front(i);
		std_merge2.push_back(i + 200);
		ft_merge2.push_back(i + 200);
	}
	std_merge.sort();
	std_merge2.sort();
	ft_merge.sort();
	ft_merge2.sort();
	std::cout << "Before merge 1st: " << std::endl << std_merge << ft_merge;
	std::cout << "Before merge 2nd: " << std::endl << std_merge2 << ft_merge2;
	std_merge.merge(std_merge2);
	ft_merge.merge(ft_merge2);
	std::cout << "After merge 1st: " << std::endl << std_merge << ft_merge;
	std::cout << "After merge 2nd: " << std::endl << std_merge2 << ft_merge2;
	}

	{
	std::list<double> std_merge(3, 7.3);
	ft::list<double> ft_merge(3, 7.3);
	std::list<double> std_merge2(2, 5.4);
	ft::list<double> ft_merge2(2, 5.4);
	for(double i = 2.3; i < 9.7; i++)
	{
		std_merge.push_back(i);
		std_merge.push_front(i);
		ft_merge.push_back(i);
		ft_merge.push_front(i);
		std_merge2.push_back(i - 0.6);
		ft_merge2.push_back(i - 0.6);
	}
	std_merge.sort();
	std_merge2.sort();
	ft_merge.sort();
	ft_merge2.sort();
	std::cout << "Before merge(compare) 1st: " << std::endl << std_merge << ft_merge;
	std::cout << "Before merge(compare) 2nd: " << std::endl << std_merge2 << ft_merge2;
	std_merge.merge(std_merge2, mycomparison);
	ft_merge.merge(ft_merge2, mycomparison);
	std::cout << "After merge(compare) 1st: " << std::endl << std_merge << ft_merge;
	std::cout << "After merge(compare) 2nd: " << std::endl << std_merge2 << ft_merge2;
	}


	// print_beautiful_title("7. TESTING NON-MEMBER OVERLOADS:");

}