#include <iostream>
#include <fstream>

int main() 
{
    setlocale(LC_ALL, "rus");

    std::ifstream file("in.txt");

    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла!" << std::endl;
        return 1;
    }

    int size;
    file >> size;

    int* array = new int[size];

    for (int i = 0; i < size; i++) { file >> array[i]; }

    for (int i = size - 1; i >= 0; i--) { std::cout << array[i] << " "; }

    delete[] array;

    file.close();

    return 0;
}
