#include <iostream>

int** create_two_dim_array(int rows, int collums);
void fill_two_dim_array(int** arr, int rows, int collums);
void print_two_dim_array(int** arr, int rows, int collums);
void delete_two_dim_array(int** arr, int rows);

int main() 
{
	setlocale(LC_ALL, "rus");

	int rows, collums;

	std::cout << "Введите количество строк: ";
	std::cin >> rows;
	std::cout << "Введите количество столбцов: ";
	std::cin >> collums;

	int** array = create_two_dim_array(rows, collums);
	fill_two_dim_array(array, rows, collums);
	print_two_dim_array(array, rows, collums);
	delete_two_dim_array(array, rows);

	return 0;
}

int** create_two_dim_array(int rows, int collums)
{
	int** arr = new int* [rows];

	for(int i{}; i < rows; i++)
	{
		arr[i] = new int[collums];
	}

	return arr;
}
void fill_two_dim_array(int** arr, int rows, int collums)
{
	for (int i{}; i < rows; i++)
	{
		for (int j{}; j < collums; j++)
		{
			arr[i][j] = (i + 1) * (j + 1);
		}
	}
}
void print_two_dim_array(int** arr, int rows, int collums) 
{
	std::cout << "Таблица умножения:" << std::endl;
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < collums; j++)
		{
			std::cout << arr[i][j];
			if (arr[i][j] < 10) std::cout << "  ";
			else std::cout << " ";
		}
		std::cout << std::endl;
	}
}
void delete_two_dim_array(int** arr, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}