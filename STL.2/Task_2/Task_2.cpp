#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>

template<typename Container>
void print_container(const Container& container)
{
    bool is_first = true;

    for (const auto& element : container) 
    {
        if (!is_first) 
        {
            std::cout << ", ";
        }
        std::cout << element;
        is_first = false;
    }
    std::cout << std::endl;
}

int main() 
{
    setlocale(LC_ALL, "Rus");

    std::set<std::string> test_set = { "один", "два", "три", "четыре" };
    std::cout << "std::set: ";
    print_container(test_set);

    std::list<std::string> test_list = { "один", "два", "три", "четыре" };
    std::cout << "std::list: ";
    print_container(test_list);

    std::vector<std::string> test_vector = { "один", "два", "три", "четыре" };
    std::cout << "std::vector: ";
    print_container(test_vector);

    return 0;
}