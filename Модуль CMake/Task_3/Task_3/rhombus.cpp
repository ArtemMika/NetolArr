#include "rhombus.h"
#include <iostream>

Rhombus::Rhombus(double side, double A, double B)
    : Parallelogram(side, side, A, B) { }

void Rhombus::print_info() const
{
    std::cout << "����:\n";
    std::cout << "�������: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}