#include <iostream>

void print(int* arr, int size);

int main()
{

	int arr1[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int arr2[]{ 6, 5, 4, 8 };
	int arr3[]{ 1, 4, 3, 7, 5 };

	print(arr1,);
}

void print(int* arr, int size)
{
	for (int value{}; value < size; ++value)
	{
		std::cout << arr[value] << " ";
	}
	std::cout << std::endl;
}