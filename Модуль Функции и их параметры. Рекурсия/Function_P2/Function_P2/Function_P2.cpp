#include <iostream>

void Func(int value, int power, int result);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");

	Func(5, 2, 1);
	Func(3, 3, 1);
	Func(4, 4, 1);
}

void Func(int value, int power, int result)
{
	for (int i = 0; i < power; i++)
	{
		result *= value;
	}

	std::cout << value << " в степени " << power << " = " << result << std::endl;
}
