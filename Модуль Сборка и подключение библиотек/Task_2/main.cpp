#include <iostream>
#include <string>
#include "Leaver.h" // Подключение заголовочного файла библиотеки
#include <Windows.h>

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string userName;

    std::cout << "Введите имя: ";
    std::getline(std::cin, userName);

    LeaverLibrary::Leaver leaver;
    std::cout << leaver.leave(userName) << std::endl;

    return 0;
}