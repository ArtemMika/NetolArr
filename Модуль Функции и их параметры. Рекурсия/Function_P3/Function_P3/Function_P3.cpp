#include <iostream>
using namespace std;

int fib_number(int n) 
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib_number(n - 1) + fib_number(n - 2);
}

void fibonacci(int count) 
{
    for (int i = 0; i < count; i++)
    {
        if (i > 0) cout << " ";
        cout << fib_number(i);
    }
}

int main() 
{
    setlocale(LC_ALL, "rus");

    int value;
    cout << "Введите число: ";
    cin >> value;
    cout << "Числа Фибоначчи: ";

    fibonacci(value);

    cout << endl;
    return 0;
}
