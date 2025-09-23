#include "right_triangle.h"

bool RightTriangle::validate() const {
	if (!Triangle::validate()) return false;
	if (angleA != 90 && angleB != 90 && angleC != 90) return false;
	return true;
}