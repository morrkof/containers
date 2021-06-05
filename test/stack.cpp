#include "test.hpp"

void test_stack()
{
    std::cout << "\e[1;32m";
	std::cout << "*****************" << std::endl;
	std::cout << "*  🍀 STACK 🍀  *" << std::endl;
	std::cout << "*****************" << std::endl;
	std::cout << "\e[0m";

    std::stack<std::string> v_stack;
	ft::stack<std::string> ft_stack;
	std::cout << "Constructor:" << std::endl << 
	"std: size = " << v_stack.size() << "  ft: size = " << ft_stack.size() << std::endl;

	std::cout << "Is empty?" << std::endl << 
	"std: empty = " << v_stack.empty() << "  ft: empty = " << ft_stack.empty() << std::endl;

	v_stack.push("hello");
	ft_stack.push("hello");

	std::cout << "Added element:" << std::endl << 
	"std: top element = " << v_stack.top() << "  ft: top element = " << ft_stack.top() << std::endl;

	std::cout << "Is empty?" << std::endl << 
	"std: empty = " << v_stack.empty() << "  ft: empty = " << ft_stack.empty() << std::endl;

	v_stack.push("world");
	ft_stack.push("world");

	std::cout << "Added another element:" << std::endl << 
	"std: top element = " << v_stack.top() << " , size = " << v_stack.size() <<
	"  ft: top element = " << ft_stack.top() << " , size = " << ft_stack.size() << std::endl;

	v_stack.pop();
	ft_stack.pop();

	std::cout << "Deleted element:" << std::endl << 
	"std: top element = " << v_stack.top() << " , size = " << v_stack.size() <<
	"  ft: top element = " << ft_stack.top() << " , size = " << ft_stack.size() << std::endl;

	std::stack<std::string> v_stack2;
	ft::stack<std::string> ft_stack2;

	std::cout << "Relational operators:" << std::endl;
	std::cout << "std : 1 == 2 ? " << (v_stack == v_stack2) << std::endl;
	std::cout << "ft  : 1 == 2 ? " << (ft_stack == ft_stack2) << std::endl;
	std::cout << "std : 1 != 2 ? " << (v_stack != v_stack2) << std::endl;
	std::cout << "ft  : 1 != 2 ? " << (ft_stack != ft_stack2) << std::endl;
	std::cout << "std : 1 > 2 ? " << (v_stack > v_stack2) << std::endl;
	std::cout << "ft  : 1 > 2 ? " << (ft_stack > ft_stack2) << std::endl;
	std::cout << "std : 1 >= 2 ? " << (v_stack >= v_stack2) << std::endl;
	std::cout << "ft  : 1 >= 2 ? " << (ft_stack >= ft_stack2) << std::endl;
	std::cout << "std : 1 < 2 ? " << (v_stack < v_stack2) << std::endl;
	std::cout << "ft  : 1 < 2 ? " << (ft_stack < ft_stack2) << std::endl;
	std::cout << "std : 1 <= 2 ? " << (v_stack <= v_stack2) << std::endl;
	std::cout << "ft  : 1 <= 2 ? " << (ft_stack <= ft_stack2) << std::endl;
}