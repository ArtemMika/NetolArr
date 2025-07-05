#include <iostream>

void swap(int& a, int& b);

int main()
{
    setlocale(LC_ALL, "rus");

    int a = 5, b = 8;
    std::cout << "a = " << a << ", b = " << b << std::endl;

    swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;

    return 0;
}

void swap(int& a, int& b)
{
    int c;
    c = a;
    a = b;
    b = c;
}
//усложнения:
/*void swap(int& a, int& b) 
{
    a = a + b;
    b = a - b;
    a = a - b;
}
*/
/*
void swap(int& a, int& b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}
*/