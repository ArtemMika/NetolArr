#include <iostream>
#include <string>
#include "../LeaverLibrary/Leaver.h"
#include <Windows.h>

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string userName;

    std::cout << "¬ведите им€: ";
    std::getline(std::cin, userName);

    // »спользуем пространство имЄн
    LeaverNamespace::Leaver leaver;
    std::cout << leaver.leave(userName) << std::endl;

    return 0;
}