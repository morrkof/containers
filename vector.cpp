#include <vector>
#include <iostream>

int main()
{
    std::cout << "Как же всё-таки работает вектор..? 🤔🤔🤔" << std::endl;
    std::vector<int> v;
    std::cout << "++" << std::endl;
    for(int i = 0; i != 18; i++)
    {
        v.push_back(42);
        std::cout << "SIZE: " << v.size() << " CAPACITY: " << v.capacity() << std::endl;
    }
    std::cout << "--" << std::endl;
    for(int i = 0; i != 5; i++)
    {
        v.pop_back();
        std::cout << "SIZE: " << v.size() << " CAPACITY: " << v.capacity() << std::endl;
    }
}