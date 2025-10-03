#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle
{
public:
    Square(double side);
    void print_info() const override;
};

#endif