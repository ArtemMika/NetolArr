#include <iostream>
#include <fstream>

int main() 
{
    setlocale(LC_ALL, "rus");
    std::ifstream inputFile("in.txt");

    if (!inputFile.is_open()) 
    {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    int rows, cols;
    inputFile >> rows >> cols;

    int** array = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        array[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            inputFile >> array[i][j];
        }
    }

    for (int i = 0; i < rows; i++) 
    {
        for (int j = cols - 1; j >= 0; j--) 
        {  
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    inputFile.close();

    for (int i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}