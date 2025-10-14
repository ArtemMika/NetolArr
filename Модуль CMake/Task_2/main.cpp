#include <iostream>
#include "figure.h"
#include "triangle.h"
#include "right_triangle.h"
#include "isosceles_triangle.h"
#include "equilateral_triangle.h"
#include "quadrangle.h"
#include "parallelogram.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"

void print_figure_info(const Figure* figure)
{
    figure->print_info();
}

int main()
{
    setlocale(LC_ALL, "rus");

    Triangle triangle("Треугольник", 10, 20, 30, 50, 60, 70);
    RightTriangle right_triangle(10, 20, 30, 50, 60);
    IsoscelesTriangle isosceles_triangle(10, 20, 50, 60);
    EquilateralTriangle equilateral_triangle(30);

    Quadrangle quadrangle("Четырёхугольник", 10, 20, 30, 40, 50, 60, 70, 80);
    Parallelogram parallelogram(20, 30, 60, 120);
    Rectangle rectangle(10, 20);
    Square square(20);
    Rhombus rhombus(15, 60, 120);

    std::cout << "Треугольник:\n";
    triangle.print_info();
    std::cout << "\n";

    std::cout << "Прямоугольный треугольник:\n";
    right_triangle.print_info();
    std::cout << "\n";

    std::cout << "Равнобедренный треугольник:\n";
    isosceles_triangle.print_info();
    std::cout << "\n";

    std::cout << "Равносторонний треугольник:\n";
    equilateral_triangle.print_info();
    std::cout << "\n";

    std::cout << "Четырёхугольник:\n";
    quadrangle.print_info();
    std::cout << "\n";

    std::cout << "Параллелограмм:\n";
    parallelogram.print_info();
    std::cout << "\n";

    std::cout << "Прямоугольник:\n";
    rectangle.print_info();
    std::cout << "\n";

    std::cout << "Квадрат:\n";
    square.print_info();
    std::cout << "\n";

    std::cout << "Ромб:\n";
    rhombus.print_info();
    std::cout << "\n";

    Figure* figures[] =
    {
        &triangle,
        &right_triangle,
        &isosceles_triangle,
        &equilateral_triangle,
        &quadrangle,
        &parallelogram,
        &rectangle,
        &square,
        &rhombus
    };

    std::cout << "Вывод через полиморфную функцию:\n";
    for (Figure* figure : figures)
    {
        print_figure_info(figure);
        std::cout << "\n";
    }

    return 0;
}
