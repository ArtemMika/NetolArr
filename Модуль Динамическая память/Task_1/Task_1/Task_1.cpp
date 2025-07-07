#include <iostream>

int main() 
{
    setlocale(LC_ALL, "rus");

    int size;

    std::cout << "Введите размер массива: ";
    std::cin >> size;

    int* arr = new int[size];

    for (int i = 0; i < size; i++) 
    {
        std::cout << "arr[" << i << "] = ";
        std::cin >> arr[i];
    }

    std::cout << "Введённый массив: ";
    for (int i = 0; i < size; i++) 
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    delete[] arr;

    return 0;
}