#ifndef QUADRANGLE_H
#define QUADRANGLE_H

#include "figure.h"

class Quadrangle : public Figure
{
protected:
    double a, b, c, d;
    double A, B, C, D;

public:
    Quadrangle(const std::string& name, double a, double b, double c, double d, double A, double B, double C, double D);
    void print_info() const override;
};

class Parallelogram : public Quadrangle
{
public:
    Parallelogram(double a, double b, double A, double B);
    void print_info() const override;
};

class Rectangle : public Parallelogram
{
public:
    Rectangle(double a, double b);
    void print_info() const override;
};

class Square : public Rectangle
{
public:
    Square(double side);
    void print_info() const override;
};

class Rhombus : public Parallelogram
{
public:
    Rhombus(double side, double A, double B);
    void print_info() const override;
};

#endif // QUADRANGLE_H