#include <iostream>
#include <clocale>

int countGreaterElements(int* arr, int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return size - left;
}

int main() 
{
    std::setlocale(LC_ALL, "");

    int arr[] = { 14, 16, 19, 32, 32, 32, 56, 69, 72 };
    int size = sizeof(arr) / sizeof(arr[0]);

    int target;

    std::cout << "Введите точку отсчёта: ";
    std::cin >> target;

    int result = countGreaterElements(arr, size, target);
    std::cout << "Количество элементов в массиве больших, чем " << target << ": " << result << std::endl;

    return 0;
}