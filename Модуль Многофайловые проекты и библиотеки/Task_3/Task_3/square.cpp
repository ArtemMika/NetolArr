#include "square.h"
#include <iostream>

Square::Square(double side)
    : Rectangle(side, side) { }

void Square::print_info() const
{
    std::cout << "�������:\n";
    std::cout << "�������: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}