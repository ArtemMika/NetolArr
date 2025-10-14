#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "parallelogram.h"

class Rhombus : public Parallelogram
{
public:
    Rhombus(double side, double A, double B);
    void print_info() const override;
};

#endif