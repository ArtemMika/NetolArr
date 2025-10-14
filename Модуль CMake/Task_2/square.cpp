#include "square.h"
#include <iostream>

Square::Square(double side) : Rectangle(side, side) {}

void Square::print_info() const
{
    std::cout << "Квадрат:\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}