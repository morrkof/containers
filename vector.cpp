#include <vector>
#include <string>
#include <iostream>
#include "Vector.hpp"

int main()
{
    std::cout << "TESTING CONSTRUCTORS:" << std::endl;
    std::vector<std::string> v_empty;
    std::cout << "std | Default constructor: size - " << v_empty.size() << ", capacity - " << v_empty.capacity() << std::endl;
    std::vector<int> v_zero(5);
    std::cout << "std | Fill constructor with default value: size - " << v_zero.size() << ", capacity - " << v_zero.capacity() 
    << ", elements: " << v_zero[0] << " " << v_zero[1] << " " << v_zero[2] << " " << v_zero[3] << " " << v_zero[4] << std::endl;
    std::vector<int> v_full(3, 42);
    std::cout << "std | Fill constructor with value = 42: size - " << v_full.size() << ", capacity - " << v_full.capacity() 
    << ", elements: " << v_full[0] << " " << v_full[1] << " " << v_full[2] << std::endl;
    std::vector<int> v_range(v_full.begin(), v_full.end());
    std::cout << "std | Range constructor (fill): size - " << v_range.size() << ", capacity - " << v_range.capacity() 
    << ", elements: " << v_range[0] << " " << v_range[1] << " " << v_range[2] << std::endl;
    std::vector<int> v_copy(v_full);
    std::cout << "std | Copy constructor (fill): size - " << v_copy.size() << ", capacity - " << v_copy.capacity() 
    << ", elements: " << v_copy[0] << " " << v_copy[1] << " " << v_copy[2] << std::endl;

    ft::vector<std::string> ft_empty;
    std::cout << "ft | Default constructor: size - " << ft_empty.size() << ", capacity - " << ft_empty.capacity() << std::endl;
    std::vector<int> ft_zero(5);
    std::cout << "ft | Fill constructor with default value: size - " << ft_zero.size() << ", capacity - " << ft_zero.capacity() 
    << ", elements: " << ft_zero[0] << " " << ft_zero[1] << " " << ft_zero[2] << " " << ft_zero[3] << " " << ft_zero[4] << std::endl;
    ft::vector<int> ft_full(3, 42);
    std::cout << "ft | Fill constructor with value = 42: size - " << ft_full.size() << ", capacity - " << ft_full.capacity() 
    << ", elements: " << ft_full[0] << " " << ft_full[1] << " " << ft_full[2] << std::endl;
    // ft::vector<int> ft_range(ft_full.begin(), ft_full.end());
    // std::cout << "ft | Range constructor (fill): size - " << ft_range.size() << ", capacity - " << ft_range.capacity() 
    // << ", elements: " << ft_range[0] << " " << ft_range[1] << " " << ft_range[2] << std::endl;
    // ft::vector<int> ft_copy(ft_full);
    // std::cout << "ft | Copy constructor (fill): size - " << ft_copy.size() << ", capacity - " << ft_copy.capacity() 
    // << ", elements: " << ft_copy[0] << " " << ft_copy[1] << " " << ft_copy[2] << std::endl;





    // std::cout << "++" << std::endl;
    // for(int i = 0; i != 18; i++)
    // {
    //     v.push_back(42);
    //     std::cout << "SIZE: " << v.size() << " CAPACITY: " << v.capacity() << std::endl;
    // }
    // std::cout << "--" << std::endl;
    // for(int i = 0; i != 5; i++)
    // {
    //     v.pop_back();
    //     std::cout << "SIZE: " << v.size() << " CAPACITY: " << v.capacity() << std::endl;
    // }

}