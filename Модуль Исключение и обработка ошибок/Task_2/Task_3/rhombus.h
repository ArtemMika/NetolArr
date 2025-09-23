#pragma once
#include "parallelogram.h"

class Rhombus : public Parallelogram 
{
private:
	double side;

public:
	Rhombus(double side, double angleA, double angleB);

	bool validate() const override;
};