#include <iostream>
#include <fstream>

int main() 
{
    setlocale(LC_ALL, "rus");

    int size;

    std::cout << "Введите размер массива: ";
    std::cin >> size;

    int* array = new int[size];

    for (int i = 0; i < size; i++)
    {
        std::cout << "arr[" << i << "] = ";
        std::cin >> array[i];
    }

    std::ofstream file("out.txt");

    if (!file.is_open()) 
    {
        std::cerr << "Ошибка при создании файла!" << std::endl;
        return 1;
    }

    file << size << std::endl;

    for (int i = size - 1; i >= 0; i--) 
    {
        file << array[i];
        if (i != 0) { file << " "; }
    }

    file.close();

    delete[] array;

    return 0;
}