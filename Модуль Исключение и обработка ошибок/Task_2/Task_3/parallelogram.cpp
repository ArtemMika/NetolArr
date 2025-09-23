#include "parallelogram.h"

Parallelogram::Parallelogram(double a, double b, double angleA, double angleB) : Quadrangle(a, b, a, b, angleA, angleB, angleA, angleB) { }

bool Parallelogram::validate() const
{
    if (!Quadrangle::validate()) return false;
    if (a != c || b != d) return false;
    if (angleA != angleC || angleB != angleD) return false;
    return true;
}