#include <iostream>
#include "parallelogram.h"


Parallelogram::Parallelogram(double a, double b, double A, double B)
    : Quadrangle("��������������", a, b, a, b, A, B, A, B) {
}

void Parallelogram::print_info() const 
{
    std::cout << "��������������:\n";
    std::cout << "�������: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "����: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}