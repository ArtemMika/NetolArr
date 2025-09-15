#include <iostream>
#include "MyMath.h"

int main() 
{
    setlocale(LC_ALL, "rus");

    double num1, num2, result;
    int choice;

    std::cout << "Введите первое число: ";
    std::cin >> num1;

    std::cout << "Введите второе число: ";
    std::cin >> num2;

    std::cout << "Выберите операцию:\n"
        << "1 - сложение\n"
        << "2 - вычитание\n"
        << "3 - умножение\n"
        << "4 - деление\n"
        << "5 - возведение в степень\n";
    std::cin >> choice;

    switch (choice) {
    case 1:
        result = add(num1, num2);
        std::cout << num1 << " + " << num2 << " = " << result << std::endl;
        break;
    case 2:
        result = subtract(num1, num2);
        std::cout << num1 << " - " << num2 << " = " << result << std::endl;
        break;
    case 3:
        result = multiply(num1, num2);
        std::cout << num1 << " * " << num2 << " = " << result << std::endl;
        break;
    case 4:
        result = divide(num1, num2);
        std::cout << num1 << " / " << num2 << " = " << result << std::endl;
        break;
    case 5:
        result = power(num1, num2);
        std::cout << num1 << " ^ " << num2 << " = " << result << std::endl;
        break;
    default:
        std::cout << "Неверный выбор операции!" << std::endl;
    }

    return 0;
}
