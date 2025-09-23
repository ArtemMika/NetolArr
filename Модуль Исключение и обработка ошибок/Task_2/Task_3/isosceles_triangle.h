#pragma once
#include "triangle.h"

class IsoscelesTriangle : public Triangle
{
public:
    IsoscelesTriangle(double a, double b, double angleA) : Triangle(a, b, a, angleA, 180 - 2 * angleA, angleA)  { }

    bool validate() const override;
};