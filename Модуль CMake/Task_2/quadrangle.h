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

#endif 