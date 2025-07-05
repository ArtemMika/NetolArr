#include <iostream>

void counting_function();

int main()
{
    setlocale(LC_ALL, "rus");

    for (int i = 0; i < 15; i++)
    {
        counting_function();
    }

    return 0;
}

void counting_function()
{
    static int count{};
    std::cout << "Количество вызовов функции counting_function(): " << ++count << std::endl;
}