#include <iostream>

//#define MODE 0  // Режим тренировки
#define MODE 1  // Боевой режим
//#define MODE 2  // Для тестирования "Неизвестный режим"

#ifndef MODE
#error Константа MODE не определена! Необходимо определить MODE перед компиляцией.
#endif

int add(int a, int b)
{
    return a + b;
}

int main()
{
    setlocale(LC_ALL, "rus");

    // Обработка различных значений MODE
#if MODE == 0
    std::cout << "Работаю в режиме тренировки" << std::endl;
#elif MODE == 1
    std::cout << "Работаю в боевом режиме" << std::endl;
    int num1, num2;

    std::cout << "Введите число 1: ";
    std::cin >> num1;

    std::cout << "Введите число 2: ";
    std::cin >> num2;

    std::cout << "Результат сложения: " << add(num1, num2) << std::endl;
#else
    std::cout << "Неизвестный режим. Завершение работы" << std::endl;
#endif

    return 0;
}