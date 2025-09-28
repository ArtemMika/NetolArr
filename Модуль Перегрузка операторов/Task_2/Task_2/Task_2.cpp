#include <iostream>
#include <numeric> // для std::gcd

class Fraction 
{
private:
    int numerator_;
    int denominator_;

    void reduce() 
    {
        int gcd = std::gcd(numerator_, denominator_);
        numerator_ /= gcd;
        denominator_ /= gcd;

        if (denominator_ < 0) 
        {
            numerator_ *= -1;
            denominator_ *= -1;
        }
    }

public:
    Fraction(int numerator, int denominator)
        : numerator_(numerator), denominator_(denominator) 
    {
        if (denominator == 0) 
        {
            throw std::invalid_argument("Знаменатель не может быть равен нулю!");
        }
        reduce();
    }

    bool operator==(const Fraction& other) const { return numerator_ * other.denominator_ == other.numerator_ * denominator_; }
    bool operator!=(const Fraction& other) const { return !(*this == other); }
    bool operator<(const Fraction& other) const  { return numerator_ * other.denominator_ < other.numerator_ * denominator_; }
    bool operator>(const Fraction& other) const  { return other < *this; }
    bool operator<=(const Fraction& other) const { return !(*this > other); }
    bool operator>=(const Fraction& other) const { return !(*this < other); }

    Fraction operator+(const Fraction& other) const 
    {
        return Fraction(numerator_ * other.denominator_ + other.numerator_ * denominator_,
            denominator_ * other.denominator_);
    }

    Fraction operator-(const Fraction& other) const 
    {
        return Fraction(numerator_ * other.denominator_ - other.numerator_ * denominator_,
            denominator_ * other.denominator_);
    }

    Fraction operator*(const Fraction& other) const 
    {
        return Fraction(numerator_ * other.numerator_, denominator_ * other.denominator_);
    }

    Fraction operator/(const Fraction& other) const 
    {
        if (other.numerator_ == 0) 
        {
            throw std::invalid_argument("Деление на ноль!");
        }
        return Fraction(numerator_ * other.denominator_, denominator_ * other.numerator_);
    }

    Fraction operator-() const 
    {
        return Fraction(-numerator_, denominator_);
    }

    Fraction& operator++()
    {
        numerator_ += denominator_;
        reduce();
        return *this;
    }

    Fraction operator++(int) 
    {
        Fraction temp = *this;
        ++*this;
        return temp;
    }

    Fraction& operator--() 
    {
        numerator_ -= denominator_;
        reduce();
        return *this;
    }

    Fraction operator--(int) 
    { 
        Fraction temp = *this;
        --*this;
        return temp;
    }

    // Вывод дроби
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) 
    {
        os << frac.numerator_ << '/' << frac.denominator_;
        return os;
    }
};

int main() 
{
    setlocale(LC_ALL, "rus");

    int num1, denom1, num2, denom2;

    std::cout << "Введите числитель дроби 1: ";
    std::cin >> num1;
    std::cout << "Введите знаменатель дроби 1: ";
    std::cin >> denom1;

    std::cout << "Введите числитель дроби 2: ";
    std::cin >> num2;
    std::cout << "Введите знаменатель дроби 2: ";
    std::cin >> denom2;

    Fraction f1(num1, denom1);
    Fraction f2(num2, denom2);

    std::cout << "\nРезультаты операций:\n";
    std::cout << f1 << " + " << f2 << " = " << (f1 + f2) << '\n';
    std::cout << f1 << " - " << f2 << " = " << (f1 - f2) << '\n';
    std::cout << f1 << " * " << f2 << " = " << (f1 * f2) << '\n';
    std::cout << f1 << " / " << f2 << " = " << (f1 / f2) << '\n';

    std::cout << "\nУнарный минус:\n";
    std::cout << "-(" << f1 << ") = " << (-f1) << '\n';

    std::cout << "\nДемонстрация инкремента:\n";
    Fraction f1_copy = f1;
    std::cout << "Префиксный инкремент: ++" << f1_copy << " = " << ++f1_copy << '\n';
    f1_copy = f1;
    std::cout << "Постфиксный инкремент: " << f1_copy << "++ = " << f1_copy++ << '\n';

    std::cout << "\nДемонстрация декремента:\n";
    f1_copy = f1;
    std::cout << "Префиксный декремент: --" << f1_copy << " = " << --f1_copy << '\n';
    f1_copy = f1;
    std::cout << "Постфиксный декремент: " << f1_copy << "-- = " << f1_copy-- << '\n';

    std::cout << "\nДемонстрация разницы инкрементов:\n";
    f1_copy = f1;
    std::cout << "Пример с постфиксным инкрементом: " << f1_copy << "++ * " << f2 << " = "
        << f1_copy++ * f2 << '\n';
    std::cout << "Значение f1 после операции: " << f1_copy << '\n';

    f1_copy = f1;
    std::cout << "Пример с префиксным инкрементом: ++" << f1_copy << " * " << f2 << " = "
        << ++f1_copy * f2 << '\n';
    std::cout << "Значение f1 после операции: " << f1_copy << '\n';

    return 0;
}