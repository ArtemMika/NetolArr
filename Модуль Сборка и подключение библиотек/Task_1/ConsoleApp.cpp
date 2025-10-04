#include <iostream>
#include <string>
#include "Greeter.h"  // Подключение заголовочного файла библиотеки
#include <Windows.h>

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string userName;

    // Запрос имени пользователя
    std::cout << "Введите имя: ";
    std::getline(std::cin, userName);

    // Создание объекта и использование метода
    GreeterLibrary::Greeter greeter;
    std::cout << greeter.greet(userName) << std::endl;

    return 0;
}