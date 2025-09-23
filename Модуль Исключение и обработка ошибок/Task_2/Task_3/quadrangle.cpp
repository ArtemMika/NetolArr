#include "quadrangle.h"
#include <sstream>

Quadrangle::Quadrangle(double a, double b, double c, double d, double angleA, double angleB, double angleC, double angleD) : a(a), b(b), c(c), d(d),
    angleA(angleA), angleB(angleB), angleC(angleC), angleD(angleD) 
{
    if (!validate()) 
    {
        throw GeometryError("Неверные параметры четырехугольника");
    }
}

bool Quadrangle::validate() const 
{
    if (a <= 0 || b <= 0 || c <= 0 || d <= 0) return false;
    if (angleA <= 0 || angleB <= 0 || angleC <= 0 || angleD <= 0) return false;
    if (angleA + angleB + angleC + angleD != 360) return false;
    return true;
}

std::string Quadrangle::getType() const { return "Четырехугольник"; }

std::string Quadrangle::getParams() const
{
    std::ostringstream oss;
    oss << "стороны " << a << ", " << b << ", " << c << ", " << d << "; "
        << "углы " << angleA << ", " << angleB << ", " << angleC << ", " << angleD;
    return oss.str();
}