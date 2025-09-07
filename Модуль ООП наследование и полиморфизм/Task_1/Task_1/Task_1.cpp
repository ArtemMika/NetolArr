#include <iostream>
#include <string>

class Figure 
{
protected:
    std::string name;
    int sides_count;

public:
    Figure() : name("Фигура"), sides_count(0) {}

    int get_sides_count() const 
    {
        return sides_count;
    }

    std::string get_name() const
    { 
        return name; 
    }
};

class Triangle : public Figure
{
public:
    Triangle() 
    {
        name = "Треугольник";
        sides_count = 3;
    }
};

class Quadrangle : public Figure 
{
public:
    Quadrangle()
    {
        name = "Четырёхугольник";
        sides_count = 4;
    }
};

int main() 
{
    setlocale(LC_ALL, "rus");

    Figure figure;
    Triangle triangle;
    Quadrangle quadrangle;

    std::cout << "Количество сторон:" << std::endl;
    std::cout << figure.get_name() << ": " << figure.get_sides_count() << std::endl;
    std::cout << triangle.get_name() << ": " << triangle.get_sides_count() << std::endl;
    std::cout << quadrangle.get_name() << ": " << quadrangle.get_sides_count() << std::endl;

    return 0;
}