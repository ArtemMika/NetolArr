#include <iostream>

void reverse(int* arr, int size);
void print(int* arr, int size);

int main()
{
    int arr[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "До функции reverse : ";
    print(arr, size);
    reverse(arr, size);

    std::cout << "После функции reverse : ";
    print(arr, size);
    
    return 0;
}

void reverse(int* arr, int size) 
{
    for (int i = 0; i < size / 2; i++) 
    {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}
void print(int* arr, int size)
{
	for (int value{}; value < size; ++value)
	{
		std::cout << arr[value] << " ";
	}
	std::cout << std::endl;
}