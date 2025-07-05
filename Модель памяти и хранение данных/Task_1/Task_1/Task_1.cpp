#include <iostream>

int main()
{
	setlocale(LC_ALL, "rus");

	int a;
	short b;
	long c;
	long long d;
	float i;
	double f;
	long double g;
	bool t;

	std::cout << "int: " << &a << "  " << sizeof(a) << std::endl;
	std::cout << "short: " << &b << "  " << sizeof(b) << std::endl;
	std::cout << "long: " << &c << "  " << sizeof(c) << std::endl;
	std::cout << "long long: " << &d << "  " << sizeof(d) << std::endl;
	std::cout << "float: " << &i << "  " << sizeof(i) << std::endl;
	std::cout << "double: " << &f << "  " << sizeof(f) << std::endl;
	std::cout << "long double: " << &g << "  " << sizeof(g) << std::endl;
	std::cout << "bool: " << &t << "  " << sizeof(t) << std::endl;

	return 0;
}