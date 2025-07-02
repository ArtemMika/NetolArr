#include <iostream>

int main() 
{
    setlocale(LC_ALL, "rus");

    int array[3][6] = 
    {
        {15, 23, 8, 14, 3, 9},
        {17, 6, 21, 4, 12, 5},
        {18, 7, 2, 11, 19, 25}
    };

    std::cout << "Массив:" << std::endl;

    int min = array[0][0];
    int max = array[0][0];
    int min_row = 0, min_col = 0;
    int max_row = 0, max_col = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 6; j++) 
        {
            std::cout << array[i][j] << "\t";

            if (array[i][j] < min) 
            {
                min = array[i][j];
                min_row = i;
                min_col = j;
            }

            if (array[i][j] > max) 
            {
                max = array[i][j];
                max_row = i;
                max_col = j;
            }
        }

        std::cout << std::endl;
    }

    std::cout << "Индекс минимального элемента: " << min_row << " " << min_col << std::endl;
    std::cout << "Индекс максимального элемента: " << max_row << " " << max_col << std::endl;

    return 0;
}
