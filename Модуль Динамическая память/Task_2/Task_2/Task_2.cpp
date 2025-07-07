#include <iostream>

double* create_array(int size) 
{
    return new double[size]();
}

int main() 
{
    setlocale(LC_ALL, "rus");

    int size;
    double* arr{};

    std::cout << "Введите размер массива: ";
    std::cin >> size;

    arr = create_array(size);

    std::cout << "Массив: ";
    for (int i = 0; i < size; i++) 
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    delete[] arr;

    return 0;
}