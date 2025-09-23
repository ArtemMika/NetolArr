#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>

class bad_length : public std::exception 
{
public:
    const char* what() const noexcept override
    {
        return "Длина строки равна запрещённому значению!";
    }
};

int getStringLength(const std::string& str, int forbidden_length) 
{
    int length = str.length();

    if (length == forbidden_length) { throw bad_length(); }

    return length;
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int forbidden_length;
    std::string input;

    std::cout << "Введите запретную длину: ";
    std::cin >> forbidden_length;

    while (true) 
    {
        std::cout << "\nВведите слово: ";
        std::cin >> input;

        try
        {
            int length = getStringLength(input, forbidden_length);
            std::cout << "Длина слова \"" << input << "\" равна " << length << std::endl;
        }
        catch (const bad_length& e) 
        {
            std::cout << "\nВы ввели слово запретной длины! До свидания\n";
            break;
        }
    }
    return 0;
}