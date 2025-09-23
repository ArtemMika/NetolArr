#include "square.h"

Square::Square(double side): Rectangle(side, side), side(side) { }

bool Square::validate() const
{
    if (!Rectangle::validate()) return false;
    if (a != b) return false;
    return true;
}