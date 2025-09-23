#pragma once
#include "triangle.h"

class RightTriangle : public Triangle {
public:
	// Исправленная сигнатура конструктора
	RightTriangle(double a, double b, double c)
		: Triangle(a, b, c, 90, (180 - 90) / 2, (180 - 90) / 2) {
	}

	bool validate() const override;
};