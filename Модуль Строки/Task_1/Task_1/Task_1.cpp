#include <iostream>
#include<string>
#include <windows.h>

int main()
{
	SetConsoleCP(1251);// только для того чтобы можно было
	SetConsoleOutputCP(1251);// писать и выводить на RUS

	std::string name;
	std::string surname;
	std::cout << "Введите имя: ";
	std::cin >> name;
	std::cout << "Введите имя : ";
	std::cin >> surname;

	std::string greeting = "Здравствуйте, " + name + " " + surname + "!";
	std::cout << greeting << std::endl;

	return 0;
}

