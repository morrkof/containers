#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> v;
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

    v.push_back("Blabla");
    std::cout << v[0] << std::endl;

    std::string *ptr = &v[0];

    v.push_back("croak");
    v.push_back("killkillkill");

    std::cout << *ptr << std::endl;

}