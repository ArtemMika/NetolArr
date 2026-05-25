#include <iostream>
#include <vector>
#include <string>
#include <iterator>

template<typename T>
void move_vectors(std::vector<T>& source, std::vector<T>& destination) 
{
    destination.insert(
        destination.end(),
        std::make_move_iterator(source.begin()),
        std::make_move_iterator(source.end())
    );
    source.clear();
}

int main()
{
    std::vector<std::string> one = { "test_string1", "test_string2" };

    std::vector<std::string> two;

    std::cout << "Before move:" << std::endl;
    std::cout << "Vector 'one' contains: ";

    for (const auto& str : one) 
    {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector 'two' contains: ";

    for (const auto& str : two) 
    {
        std::cout << str << " ";
    }

    std::cout << std::endl << std::endl;

    move_vectors(one, two);

    std::cout << "After move:" << std::endl;
    std::cout << "Vector 'one' contains (should be empty): ";

    for (const auto& str : one) 
    {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector 'two' contains (should have all elements): ";

    for (const auto& str : two) 
    {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}