#include <iostream>

class Fraction {
private:
    int numerator_;
    int denominator_;

public:
    Fraction(int numerator, int denominator)
        : numerator_(numerator), denominator_(denominator) {
    }

    // Оператор сравнения на равенство
    bool operator==(const Fraction& other) const {
        return numerator_ * other.denominator_ == other.numerator_ * denominator_;
    }

    // Оператор сравнения на неравенство
    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    // Оператор "меньше"
    bool operator<(const Fraction& other) const {
        return numerator_ * other.denominator_ < other.numerator_ * denominator_;
    }

    // Оператор "больше"
    bool operator>(const Fraction& other) const {
        return other < *this;
    }

    // Оператор "меньше или равно"
    bool operator<=(const Fraction& other) const {
        return !(*this > other);
    }

    // Оператор "больше или равно"
    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }
};

int main() {
    Fraction f1(4, 3);
    Fraction f2(6, 11);

    std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
    std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
    std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
    std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
    std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
    std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';

    return 0;
}