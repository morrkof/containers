#include "test.hpp"

void test_queue()
{
    std::cout << "\e[1;32m";
	std::cout << "*****************" << std::endl;
	std::cout << "*  🍀 QUEUE 🍀  *" << std::endl;
	std::cout << "*****************" << std::endl;
	std::cout << "\e[0m";

    std::queue<std::string> v_queue;
	ft::queue<std::string> ft_queue;
	std::cout << "Constructor:" << std::endl << 
	"std: size = " << v_queue.size() << "  ft: size = " << ft_queue.size() << std::endl;

	std::cout << "Is empty?" << std::endl << 
	"std: empty = " << v_queue.empty() << "  ft: empty = " << ft_queue.empty() << std::endl;

	v_queue.push("hello");
	ft_queue.push("hello");

	std::cout << "Added element:" << std::endl << 
	"std: back element = " << v_queue.back() << "  ft: back element = " << ft_queue.back() << std::endl;

	std::cout << "Is empty?" << std::endl << 
	"std: empty = " << v_queue.empty() << "  ft: empty = " << ft_queue.empty() << std::endl;

	v_queue.push("world");
	ft_queue.push("world");

	std::cout << "Added another element:" << std::endl << 
	"std: back element = " << v_queue.back() << " , size = " << v_queue.size() <<
	"  ft: back element = " << ft_queue.back() << " , size = " << ft_queue.size() << std::endl;

	v_queue.pop();
	ft_queue.pop();

	std::cout << "Deleted element:" << std::endl << 
	"std: back element = " << v_queue.back() << " , size = " << v_queue.size() <<
	"  ft: back element = " << ft_queue.back() << " , size = " << ft_queue.size() << std::endl;

// add front

	std::queue<std::string> v_queue2;
	ft::queue<std::string> ft_queue2;

	std::cout << "Relational operators:" << std::endl;
	std::cout << "std : 2 < 1? " << (v_queue2 < v_queue) << std::endl;
	std::cout << "ft  : 2 < 1? " << (ft_queue2 < ft_queue) << std::endl;


	std::cout << "std : 1 == 2 ? " << (v_queue == v_queue2) << std::endl;
	std::cout << "ft  : 1 == 2 ? " << (ft_queue == ft_queue2) << std::endl;
	std::cout << "std : 1 != 2 ? " << (v_queue != v_queue2) << std::endl;
	std::cout << "ft  : 1 != 2 ? " << (ft_queue != ft_queue2) << std::endl;
	std::cout << "std : 1 > 2 ? " << (v_queue > v_queue2) << std::endl;
	std::cout << "ft  : 1 > 2 ? " << (ft_queue > ft_queue2) << std::endl; // err
	std::cout << "std : 1 >= 2 ? " << (v_queue >= v_queue2) << std::endl;
	std::cout << "ft  : 1 >= 2 ? " << (ft_queue >= ft_queue2) << std::endl;
	std::cout << "std : 1 < 2 ? " << (v_queue < v_queue2) << std::endl;
	std::cout << "ft  : 1 < 2 ? " << (ft_queue < ft_queue2) << std::endl;
	std::cout << "std : 1 <= 2 ? " << (v_queue <= v_queue2) << std::endl;
	std::cout << "ft  : 1 <= 2 ? " << (ft_queue <= ft_queue2) << std::endl; // err
}