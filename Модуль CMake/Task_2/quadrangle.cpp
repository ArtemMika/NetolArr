#include "quadrangle.h"
#include <iostream>

Quadrangle::Quadrangle(const std::string& name, double a, double b, double c, double d, double A, double B, double C, double D) : Figure(name), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

void Quadrangle::print_info() const
{
    std::cout << get_name() << ":\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}