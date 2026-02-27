#include <iostream>
#include <vector>
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

std::vector<long long> memo;

long long fibonacci_dp(int n) {
    if (n <= 1) {
        return n;
    }

    if (memo[n] != -1) {
        return memo[n];
    }

    memo[n] = fibonacci_dp(n - 1) + fibonacci_dp(n - 2);
    return memo[n];
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

    memo.assign(n + 1, -1);
    long long result = fibonacci_dp(n);
    std::cout << "F(" << n << ") = " << result << std::endl;

    return 0;
}