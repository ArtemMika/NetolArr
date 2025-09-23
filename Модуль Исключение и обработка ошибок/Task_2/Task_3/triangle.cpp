#include "triangle.h"
#include <sstream>

Triangle::Triangle(double a, double b, double c,
    double angleA, double angleB, double angleC) : a(a), b(b), c(c),
    angleA(angleA), angleB(angleB), angleC(angleC)
{
    if (!validate()) 
    {
        throw GeometryError("Неверные параметры треугольника");
    }
}

bool Triangle::validate() const 
{
    if (a <= 0 || b <= 0 || c <= 0) return false;
    if (angleA <= 0 || angleB <= 0 || angleC <= 0) return false;
    if (angleA + angleB + angleC != 180) return false;
    if (a + b <= c || a + c <= b || b + c <= a) return false;
    return true;
}

std::string Triangle::getType() const 
{
    return "Треугольник";
}

std::string Triangle::getParams() const 
{
    std::ostringstream oss;
    oss << "стороны " << a << ", " << b << ", " << c << "; " << "углы " << angleA << ", " << angleB << ", " << angleC;
    return oss.str();
}