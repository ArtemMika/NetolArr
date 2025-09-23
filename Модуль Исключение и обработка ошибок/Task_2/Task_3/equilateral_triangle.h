#pragma once
#include "triangle.h"

class EquilateralTriangle : public Triangle 
{
public:
    EquilateralTriangle(double a) : Triangle(a, a, a, 60, 60, 60)  { }

    bool validate() const override;
};