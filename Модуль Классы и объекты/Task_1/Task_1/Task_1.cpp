#include <iostream>
using namespace std;

class Calculator {
private:
    double num1;
    double num2;

public:
    bool set_num1(double num) 
    {
        if (num != 0) 
        {
            this->num1 = num;
            return true;
        }
        return false;
    }

    bool set_num2(double num) 
    {
        if (num != 0) 
        {
            this->num2 = num;
            return true;
        }
        return false;
    }

    double add() 
    {
        return num1 + num2;
    }

    double multiply() 
    {
        return num1 * num2;
    }

    double subtract_1_2()
    {
        return num1 - num2;
    }

    double subtract_2_1()
    {
        return num2 - num1;
    }

    double divide_1_2()
    {
        return num1 / num2;
    }

    double divide_2_1() 
    {
        return num2 / num1;
    }
};

int main() 
{
    setlocale(LC_ALL, "rus");

    Calculator calc;
    double input1, input2;

    while (true)
    {
        cout << "Введите num1: ";
        cin >> input1;

        if (!calc.set_num1(input1))
        {
            cout << "Неверный ввод! Число не должно быть равно 0" << endl;
            continue;
        }

        cout << "Введите num2: ";
        cin >> input2;

        if (!calc.set_num2(input2))
        {
            cout << "Неверный ввод! Число не должно быть равно 0" << endl;
            continue;
        }

        cout << "num1 + num2 = " << calc.add() << endl;
        cout << "num1 - num2 = " << calc.subtract_1_2() << endl;
        cout << "num2 - num1 = " << calc.subtract_2_1() << endl;
        cout << "num1 * num2 = " << calc.multiply() << endl;
        cout << "num1 / num2 = " << calc.divide_1_2() << endl;
        cout << "num2 / num1 = " << calc.divide_2_1() << endl;
        cout << endl;
    }

    return 0;
}
