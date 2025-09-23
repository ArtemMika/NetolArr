#pragma once
#include "quadrangle.h"

class Rectangle : public Quadrangle {
public:
    // ����������� � ����� �����������
    Rectangle(double width, double height);

    // ����������� � ������ ������� ���������� (��� ������������)
    Rectangle(double a, double b, double c, double d,
        double angleA, double angleB, double angleC, double angleD);

    bool validate() const override;
};