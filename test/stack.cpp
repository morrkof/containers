#include "test.hpp"

void test_stack()
{
    std::cout << "\e[1;32m";
	std::cout << "*****************" << std::endl;
	std::cout << "*  🍀 STACK 🍀  *" << std::endl;
	std::cout << "*****************" << std::endl;
	std::cout << "\e[0m";

    print_beautiful_title("1. TESTING CONSTRUCTOR:");

    std::stack<std::string> v_empty;
	ft::stack<std::string> ft_empty;
	std::cout << "Empty constructor:" << std::endl 
    << "std | size = " << v_empty.size() << "  ft  | size = " << ft_empty.size() << std::endl;

// is empty? pushback! is empty?  pushback! popback! print top element


    std::cout << std::endl << "............. PUSH_BACK:" << std::endl;


}