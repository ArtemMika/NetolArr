#include "equilateral_triangle.h"

bool EquilateralTriangle::validate() const 
{
    if (!Triangle::validate()) return false;
    if (a != b || b != c || angleA != 60 || angleB != 60 || angleC != 60) return false;
    return true;
}