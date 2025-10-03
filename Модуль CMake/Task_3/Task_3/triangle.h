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

#endif