#include "triangle.h"
#include "right_triangle.h"
#include "rectangle.h"
#include "square.h"
#include "parallelogram.h"
#include "rhombus.h"
#include "geometry_error.h"
#include <iostream>

void testFigure(const Figure& figure)
{
	try 
	{
		std::cout << figure.getType() << " ("
			<< figure.getParams() << ") создан\n";
	}
	catch (const GeometryError& e)
	{
		std::cerr << "Ошибка создания фигуры. Причина: "
			<< e.what() << '\n';
	}
}

int main() 
{
	setlocale(LC_ALL, "rus");

	try 
	{
		// Тестирование правильных фигур
		std::cout << "Тестирование треугольников:\n";
		testFigure(Triangle(3, 4, 5, 30, 60, 90));

		// Правильный вызов для RightTriangle
		testFigure(RightTriangle(3, 4, 5));

		std::cout << "\nТестирование четырехугольников:\n";

		// Правильный вызов для Rectangle
		testFigure(Rectangle(10, 20));
		testFigure(Square(20));
		testFigure(Parallelogram(20, 30, 30, 150));
		testFigure(Rhombus(30, 30, 150));

		// Тестирование неправильных фигур
		std::cout << "\nТестирование неправильных фигур:\n";
		try {
			testFigure(Triangle(1, 2, 3, 40, 50, 90)); // Сумма углов != 180
		}
		catch (const GeometryError& e) 
		{
			std::cerr << "Ошибка: " << e.what() << '\n';
		}

		try {
			// Правильный вызов для проверки ошибки
			testFigure(RightTriangle(3, 4, 5));
		}
		catch (const GeometryError& e) 
		{
			std::cerr << "Ошибка: " << e.what() << '\n';
		}

		try {
			testFigure(Rectangle(10, 20, 10, 21, 90, 90, 90, 90)); // Неправильный прямоугольник
		}
		catch (const GeometryError& e) 
		{
			std::cerr << "Ошибка: " << e.what() << '\n';
		}

	}
	catch (const GeometryError& e) 
	{
		std::cerr << "Критическая ошибка: " << e.what() << '\n';
		return 1;
	}

	return 0;
}