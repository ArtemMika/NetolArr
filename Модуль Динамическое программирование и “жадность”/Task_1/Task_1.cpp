#include <iostream>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif

void setup_locale() {
#ifdef _WIN32
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(CP_UTF8);
#else
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif
}

long long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    setup_locale();

    int n;
    std::cout << "Введите номер числа Фибоначчи (n): ";
    std::cin >> n;

    if (n < 0) {
        std::cout << "Ошибка: n должно быть неотрицательным числом." << std::endl;
        return 1;
    }

    long long result = fibonacci(n);
    std::cout << "F(" << n << ") = " << result << std::endl;

    return 0;
}