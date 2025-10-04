#include <iostream>
#include <string>
#include "Greeter.h"  // ����������� ������������� ����� ����������
#include <Windows.h>

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string userName;

    // ������ ����� ������������
    std::cout << "������� ���: ";
    std::getline(std::cin, userName);

    // �������� ������� � ������������� ������
    GreeterLibrary::Greeter greeter;
    std::cout << greeter.greet(userName) << std::endl;

    return 0;
}