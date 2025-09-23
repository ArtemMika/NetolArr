#pragma once
#include "figure.h"
#include "geometry_error.h"

class Triangle : public Figure {
protected:
	double a, b, c;
	double angleA, angleB, angleC;

public:
	Triangle(double a, double b, double c,
		double angleA, double angleB, double angleC);

	std::string getType() const override;
	std::string getParams() const override;
	bool validate() const override;
};