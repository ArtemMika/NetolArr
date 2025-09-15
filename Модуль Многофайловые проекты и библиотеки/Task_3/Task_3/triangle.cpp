#include "triangle.h"
#include <iostream>

Triangle::Triangle(const std::string& name, double a, double b, double c, double A, double B, double C)
    : Figure(name), a(a), b(b), c(c), A(A), B(B), C(C) {
}

void Triangle::print_info() const {
    std::cout << get_name() << ":\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n";
}

RightTriangle::RightTriangle(double a, double b, double c, double A, double B)
    : Triangle("Прямоугольный треугольник", a, b, c, A, B, 90.0) {
}

IsoscelesTriangle::IsoscelesTriangle(double a, double b, double A, double B)
    : Triangle("Равнобедренный треугольник", a, b, a, A, B, A) {
}

EquilateralTriangle::EquilateralTriangle(double side)
    : Triangle("Равносторонний треугольник", side, side, side, 60.0, 60.0, 60.0) {
}