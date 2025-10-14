#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(double a, double b) : Parallelogram(a, b, 90.0, 90.0) {}

void Rectangle::print_info() const
{
    std::cout << "Прямоугольник:\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}