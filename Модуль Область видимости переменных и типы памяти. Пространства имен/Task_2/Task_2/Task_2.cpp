#include <iostream>

namespace Calculator 
{
    namespace Addition
    {
        int calc(int x, int y)
        {
            return x + y;
        }
    }
    namespace Subtraction
    {
        int calc(int x, int y)
        {
            return x - y;
        }
    }
    namespace Multiplication
    {
        int calc(int x, int y)
        {
            return x * y;
        }
    }
    namespace Division
    {
        int calc(int x, int y)
        {
            if (y == 0) return 0;
            return x / y;
        }
    }
}

int main() 
{
    setlocale(LC_ALL, "rus");

    int x = 6;
    int y = 9;

    std::cout << "x = " << x << ", y = " << y << std::endl;

    std::cout << "Сложение: " << Calculator::Addition::calc(x, y) << std::endl;
    std::cout << "Вычитание: " << Calculator::Subtraction::calc(x, y) << std::endl;
    std::cout << "Умножение: " << Calculator::Multiplication::calc(x, y) << std::endl;
    std::cout << "Деление: " << Calculator::Division::calc(x, y) << std::endl;

    return 0;
}


