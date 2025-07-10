#include <iostream>
#include<string>
#include <windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string secretWord = "малина";
	std::string user;
	bool isGuessed = false;

    do 
    {
        std::cout << "Угадайте слово: ";
        std::cin >> user;

        if (user == secretWord) {
            std::cout << "Правильно! Вы победили! Загаданное слово — " << secretWord << std::endl;
            isGuessed = true;
        }
        else {
            std::cout << "Неправильно" << std::endl;
        }
    } while (!isGuessed);

    return 0;
}