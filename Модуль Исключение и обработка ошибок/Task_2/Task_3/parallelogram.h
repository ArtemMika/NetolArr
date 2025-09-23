#pragma once
#include "quadrangle.h"

class Parallelogram : public Quadrangle 
{
public:
	Parallelogram(double a, double b, double angleA, double angleB);

	bool validate() const override;
};