#pragma once
#include "rectangle.h"

class Square : public Rectangle {
private:
	double side;

public:
	Square(double side);

	bool validate() const override;
};