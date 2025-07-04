#include <iostream>

int main() 
{

    setlocale(LC_ALL, "rus");

    int numbers[] = { 5, 23, 7, 14, 1, 9, 17, 6, 21, 4 };

    std::cout << "Массив: ";

    int min = numbers[0];
    int max = numbers[0];

    for (int i = 0; i < 10; i++) 
    {
        std::cout << numbers[i] << " ";

        if (numbers[i] < min) { min = numbers[i]; }
        if (numbers[i] > max) { max = numbers[i]; }
    }

    std::cout << std::endl;

    std::cout << "Минимальный элемент: " << min << std::endl;
    std::cout << "Максимальный элемент: " << max << std::endl;

    return 0;
}