#pragma once
#include "figure.h"
#include "geometry_error.h"

class Quadrangle : public Figure
{
protected:  // Изменили на protected
    double a, b, c, d;
    double angleA, angleB, angleC, angleD;

public:
    Quadrangle(double a, double b, double c, double d,
        double angleA, double angleB, double angleC, double angleD);

    std::string getType() const override;
    std::string getParams() const override;
    bool validate() const override;
};