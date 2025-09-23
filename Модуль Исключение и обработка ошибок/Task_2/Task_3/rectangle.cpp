#include "rectangle.h"

// ���������� ��������� ������������
Rectangle::Rectangle(double width, double height)
    : Quadrangle(width, height, width, height, 90, 90, 90, 90) {
}

// ���������� ������� ������������
Rectangle::Rectangle(double a, double b, double c, double d,
    double angleA, double angleB, double angleC, double angleD)
    : Quadrangle(a, b, c, d, angleA, angleB, angleC, angleD) {
}

bool Rectangle::validate() const {
    if (!Quadrangle::validate()) return false;
    if (a != c || b != d) return false;
    return true;
}