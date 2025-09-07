#include <iostream>
#include <string>

class Figure
{
protected:
    std::string name;

public:
    Figure(const std::string& name) : name(name) {}
    virtual ~Figure() = default;

    virtual void print_info() const = 0;
    std::string get_name() const { return name; }
};

class Triangle : public Figure 
{
protected:
    double a, b, c;
    double A, B, C;

public:
    Triangle(const std::string& name, double a, double b, double c, double A, double B, double C) : Figure(name), a(a), b(b), c(c), A(A), B(B), C(C) { }

    virtual void print_info() const override 
    {
        std::cout << get_name() << ":\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n";
    }
};

class RightTriangle : public Triangle
{
public:
    RightTriangle(double a, double b, double c, double A, double B) : Triangle("Прямоугольный треугольник", a, b, c, A, B, 90.0) { }
};

class IsoscelesTriangle : public Triangle
{
public:
    IsoscelesTriangle(double a, double b, double A, double B) : Triangle("Равнобедренный треугольник", a, b, a, A, B, A) { }
};

class EquilateralTriangle : public Triangle
{
public:
    EquilateralTriangle(double side) : Triangle("Равносторонний треугольник", side, side, side, 60.0, 60.0, 60.0) { }
};

class Quadrangle : public Figure 
{
protected:
    double a, b, c, d;
    double A, B, C, D;

public:
    Quadrangle(const std::string& name, double a, double b, double c, double d, double A, double B, double C, double D) : Figure(name), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) { }

    virtual void print_info() const override
    {
        std::cout << get_name() << ":\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }
};

class Parallelogram : public Quadrangle 
{
public:
    Parallelogram(double a, double b, double A, double B) : Quadrangle("Параллелограмм", a, b, a, b, A, B, A, B) { }

    void print_info() const override
    {
        std::cout << "Параллелограмм:\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }
};

class Rectangle : public Parallelogram 
{
public:
    Rectangle(double a, double b) : Parallelogram(a, b, 90.0, 90.0) { }

    void print_info() const override 
    {
        std::cout << "Прямоугольник:\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }
};

class Square : public Rectangle 
{
public:
    Square(double side) : Rectangle(side, side) { }

    void print_info() const override
    {
        std::cout << "Квадрат:\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }
};

class Rhombus : public Parallelogram
{
public:
    Rhombus(double side, double A, double B) : Parallelogram(side, side, A, B) { }

    void print_info() const override 
    {
        std::cout << "Ромб:\n";
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }
};

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