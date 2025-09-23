#include "rhombus.h"

Rhombus::Rhombus(double side, double angleA, double angleB) : Parallelogram(side, side, angleA, angleB) { }

bool Rhombus::validate() const 
{
    if (!Parallelogram::validate()) return false;
    if (a != b) return false;
    return true;
}