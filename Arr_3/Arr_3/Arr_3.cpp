#include <iostream>

int main()
{
    setlocale(LC_ALL, "rus");

    const int size{ 10 };
    int rows[size] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::cout << "Массив: ";

    int min = rows[size];
    int max = rows[size];


    for (int element{}; element < size; element++)
    {
        std::cout << rows[element] << " ";

        if (rows[element] < min) { min = rows[element]; }
        if (rows[element] > max) { max = rows[element]; }
    }

    std::cout << std::endl << "Минимальный элемент: " << min << std::endl;
    std::cout << "Максимальный элемент: " << max << std::endl;

    return 0;
}