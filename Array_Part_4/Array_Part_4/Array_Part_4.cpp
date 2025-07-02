#include <iostream>

int main() 
{
    setlocale(LC_ALL, "rus");

    int array[10] = { 10, 3, 4, 1, 8, 9, 7, 2, 6, 5 };

    std::cout << "Массив до сортировки: ";

    for (int i = 0; i < 10; i++) {
        std::cout << array[i] << " ";
    }

    std::cout << std::endl;

    bool swapped;

    do 
    {
        swapped = false;

        for (int i = 9; i > 0; i--)
        {
            if (array[i] < array[i - 1]) 
            {
                int temp = array[i];
                array[i] = array[i - 1];
                array[i - 1] = temp;

                swapped = true;
            }
        }
    } while (swapped);

    std::cout << "Массив после сортировки: ";
    for (int i = 0; i < 10; i++) { std::cout << array[i] << " "; }

    std::cout << std::endl;

    return 0;
}