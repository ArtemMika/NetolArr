#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : public Figure
{
protected:
    double a, b, c;
    double A, B, C;

public:
    Triangle(const std::string& name, double a, double b, double c, double A, double B, double C);
    void print_info() const override;
};

class RightTriangle : public Triangle
{
public:
    RightTriangle(double a, double b, double c, double A, double B);
};

class IsoscelesTriangle : public Triangle
{
public:
    IsoscelesTriangle(double a, double b, double A, double B);
};

class EquilateralTriangle : public Triangle
{
public:
    EquilateralTriangle(double side);
};

#endif // TRIANGLE_H