#pragma once
#include "quadrangle.h"

class Rectangle : public Quadrangle {
public:
    //  онструктор с двум€ параметрами
    Rectangle(double width, double height);

    //  онструктор с полным набором параметров (дл€ тестировани€)
    Rectangle(double a, double b, double c, double d,
        double angleA, double angleB, double angleC, double angleD);

    bool validate() const override;
};