#include <iostream>


int main()
{
    const int size{ 10 };
    int rows[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


    for (int element{}; element < size; element++)
    {
        std::cout << rows[element];
        if (element < 9)
        {
            std::cout << ", ";
        }
    }

    return 0;
}
