#include "MyMath.h"
#include <iostream>

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        std::cout << "Ошибка: деление на ноль!" << std::endl;
        return 0;
    }
    return a / b;
}

double power(double base, double exponent) {
    return std::pow(base, exponent);
}