#include "quadrangle.h"
#include <iostream>

Quadrangle::Quadrangle(const std::string& name, double a, double b, double c, double d, double A, double B, double C, double D)
    : Figure(name), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {
}

void Quadrangle::print_info() const {
    std::cout << get_name() << ":\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}

Parallelogram::Parallelogram(double a, double b, double A, double B)
    : Quadrangle("Параллелограмм", a, b, a, b, A, B, A, B) {
}

void Parallelogram::print_info() const {
    std::cout << "Параллелограмм:\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}

Rectangle::Rectangle(double a, double b)
    : Parallelogram(a, b, 90.0, 90.0) {
}

void Rectangle::print_info() const {
    std::cout << "Прямоугольник:\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}

Square::Square(double side)
    : Rectangle(side, side) {
}

void Square::print_info() const {
    std::cout << "Квадрат:\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}

Rhombus::Rhombus(double side, double A, double B)
    : Parallelogram(side, side, A, B) {
}

void Rhombus::print_info() const {
    std::cout << "Ромб:\n";
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
}