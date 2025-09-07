#include <iostream>
#include <string>

class Figure 
{
protected:
    std::string name;
    int sides_count;

public:
    Figure(const std::string& name, int sides) : name(name), sides_count(sides) {}

    virtual bool check() const
    {
        return sides_count == 0;
    }

    virtual void print_info() const
    {
        std::cout << name << ":\n";
        std::cout << (check() ? "Правильная" : "Неправильная") << "\n";
        std::cout << "Количество сторон: " << sides_count << "\n";
    }
};

class Triangle : public Figure 
{
protected:
    double a, b, c;
    double A, B, C;

public:
    Triangle(const std::string& name, double a, double b, double c, double A, double B, double C) : Figure(name, 3), a(a), b(b), c(c), A(A), B(B), C(C) {
    }

    bool check() const override 
    {
        return Figure::check() &&
            (A + B + C == 180);
    }

    void print_info() const override 
    {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n";
    }
};

class RightTriangle : public Triangle 
{
public:
    RightTriangle(double a, double b, double c, double A, double B) : Triangle("Прямоугольный треугольник", a, b, c, A, B, 90) { }

    bool check() const override 
    {
        return Triangle::check() &&
            (C == 90);
    }
};

class IsoscelesTriangle : public Triangle
{
public:
    IsoscelesTriangle(double a, double b, double A, double B) : Triangle("Равнобедренный треугольник", a, b, a, A, B, A) { }

    bool check() const override
    {
        return Triangle::check() &&
            (a == c) &&
            (A == C);
    }
};

class EquilateralTriangle : public Triangle 
{
public:
    EquilateralTriangle(double side) : Triangle("Равносторонний треугольник", side, side, side, 60, 60, 60)  { }

    bool check() const override 
    {
        return Triangle::check() &&
            (a == b && b == c) &&
            (A == B && B == C && C == 60);
    }
};

class Quadrangle : public Figure 
{
protected:
    double a, b, c, d;
    double A, B, C, D;

public:
    Quadrangle(const std::string& name, double a, double b, double c, double d, double A, double B, double C, double D) : Figure(name, 4), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) 
    { }

    bool check() const override 
    {
        return Figure::check() &&
            (A + B + C + D == 360);
    }

    void print_info() const override 
    {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }
};
class Rectangle : public Quadrangle
{
public:
    Rectangle(double a, double b) : Quadrangle("Прямоугольник", a, b, a, b, 90, 90, 90, 90) { }

    bool check() const override 
    {
        return Quadrangle::check() &&
            (a == c) && (b == d) &&
            (A == 90) && (B == 90) &&
            (C == 90) && (D == 90);
    }
};

class Square : public Quadrangle 
{
public:
    Square(double side) : Quadrangle("Квадрат", side, side, side, side, 90, 90, 90, 90) {
    }

    bool check() const override 
    {
        return Quadrangle::check() &&
            (a == b) && (b == c) && (c == d) &&
            (A == 90) && (B == 90) &&
            (C == 90) && (D == 90);
    }
};

class Parallelogram : public Quadrangle
{
public:
    Parallelogram(double a, double b, double angleA, double angleB) : Quadrangle("Параллелограмм", a, b, a, b, angleA, angleB, angleA, angleB) { }

    bool check() const override
    {
        return Quadrangle::check() &&
            (a == c) && (b == d) &&
            (A == C) && (B == D);
    }
};

class Rhombus : public Quadrangle 
{
public:
    Rhombus(double side, double angleA, double angleB) : Quadrangle("Ромб", side, side, side, side, angleA, angleB, angleA, angleB) { }

    bool check() const override 
    {
        return Quadrangle::check() &&
            (a == b) && (b == c) && (c == d) &&
            (A == C) && (B == D);
    }
};

int main() 
{
    setlocale(LC_ALL, "rus");

    std::unique_ptr<Figure> figures[] = 
    {
        std::make_unique<Figure>("Фигура", 0),
        std::make_unique<Triangle>("Треугольник", 10, 20, 30, 50, 60, 70),
        std::make_unique<RightTriangle>(10, 20, 30, 50, 40),
        std::make_unique<IsoscelesTriangle>(10, 20, 50, 60),
        std::make_unique<EquilateralTriangle>(30),
        std::make_unique<Quadrangle>("Четырёхугольник", 10, 20, 30, 40, 50, 60, 70, 80),
        std::make_unique<Rectangle>(10, 20),
        std::make_unique<Square>(20),
        std::make_unique<Parallelogram>(20, 30, 30, 40),
        std::make_unique<Rhombus>(30, 30, 40)
    };

    for (const auto& figure : figures) 
    {
        figure->print_info();
        std::cout << std::endl;
    }

    return 0;
}