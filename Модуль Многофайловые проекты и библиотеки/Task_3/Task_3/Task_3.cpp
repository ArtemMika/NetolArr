#include <iostream>
#include "figure.h"
#include "triangle.h"
#include "quadrangle.h"

void print_figure_info(const Figure* figure) {
    figure->print_info();
}

int main() {
    setlocale(LC_ALL, "rus");

    Triangle triangle("Треугольник", 10, 20, 30, 50, 60, 70);
    RightTriangle right_triangle(10, 20, 30, 50, 60);
    IsoscelesTriangle isosceles_triangle(10, 20, 50, 60);
    EquilateralTriangle equilateral_triangle(30);

    Quadrangle quadrangle("Четырёхугольник", 10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle rectangle(10, 20);
    Square square(20);
    Parallelogram parallelogram(20, 30, 30, 40);
    Rhombus rhombus(30, 30, 40);

    std::cout << std::endl;
    print_figure_info(&triangle);
    std::cout << std::endl;
    print_figure_info(&right_triangle);
    std::cout << std::endl;
    print_figure_info(&isosceles_triangle);
    std::cout << std::endl;
    print_figure_info(&equilateral_triangle);

    std::cout << std::endl;
    print_figure_info(&quadrangle);
    std::cout << std::endl;
    print_figure_info(&rectangle);
    std::cout << std::endl;
    print_figure_info(&square);
    std::cout << std::endl;
    print_figure_info(&parallelogram);
    std::cout << std::endl;
    print_figure_info(&rhombus);

    return 0;
}