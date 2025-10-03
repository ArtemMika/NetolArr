#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "quadrangle.h"

class Parallelogram : public Quadrangle
{
public:
    Parallelogram(double a, double b, double A, double B);
    void print_info() const override;
};

#endif