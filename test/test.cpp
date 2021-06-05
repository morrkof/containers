#include "test.hpp"

std::ostream &operator<<(std::ostream &os, Awesome const &i){
	os << i.getN();
	return os;
}

void print_beautiful_title(std::string str)
{
	std::cout << "\e[1;33m";
    std::cout << std::endl;
    for (int i = 0; i < 8; i++)
        std::cout << "✨";
    int a = (40 - str.size()) / 2;
    for (int i = 0; i < a; i++)
        std::cout << " ";
    std::cout << str;
    for (int i = 0; i < a; i++)
        std::cout << " ";
    if (str.size() % 2)
        std::cout << " ";
    for (int i = 0; i < 8; i++)
        std::cout << "✨";
    std::cout << std::endl;
	std::cout << "\e[0m";
}

int main()
{
	// test_vector();
	// test_list();
	test_map();
	// test_stack();
	// test_queue();

}