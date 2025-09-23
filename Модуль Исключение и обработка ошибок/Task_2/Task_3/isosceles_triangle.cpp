#include "isosceles_triangle.h"

bool IsoscelesTriangle::validate() const
{
    if (!Triangle::validate()) return false;
    if (a != c || angleA != angleC) return false;
    return true;
}