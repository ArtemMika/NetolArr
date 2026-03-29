#include <stdio.h>

void swap(int* a, int* b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int low, int high) 
{
    int pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++) 
    {
        if (arr[j] <= pivot) 
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortRecursive(int* arr, int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(arr, low, high);

        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}

void quick_sort(int* arr, int size)
{
    quickSortRecursive(arr, 0, size - 1);
}

void printArray(int* arr, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() 
{
    int arr1[] = { 3, 43, 38, 29, 18, 72, 57, 61, 2, 33 };
    int size1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Исходный массив: ");
    printArray(arr1, size1);
    quick_sort(arr1, size1);
    printf("Отсортированный массив: ");
    printArray(arr1, size1);
    printf("\n");

    int arr2[] = { 88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74 };
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Исходный массив: ");
    printArray(arr2, size2);
    quick_sort(arr2, size2);
    printf("Отсортированный массив: ");
    printArray(arr2, size2);
    printf("\n");

    int arr3[] = { 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62 };
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Исходный массив: ");
    printArray(arr3, size3);
    quick_sort(arr3, size3);
    printf("Отсортированный массив: ");
    printArray(arr3, size3);

    return 0;
}