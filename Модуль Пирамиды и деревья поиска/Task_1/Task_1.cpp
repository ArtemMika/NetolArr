#include <stdio.h>
#include <locale.h>


void print_pyramid_element(int level, int parent_value, int is_root, int is_left, int value) 
{
    if (is_root) 
    {
        printf("%d root %d\n", level, value);
    }
    else if (is_left)
    {
        printf("%d left(%d) %d\n", level, parent_value, value);
    }
    else
    {
        printf("%d right(%d) %d\n", level, parent_value, value);
    }
}

void print_pyramid(int arr[], int size) 
{
    if (size == 0) 
    {
        return;
    }

    print_pyramid_element(0, 0, 1, 0, arr[0]);

    int level = 1;
    int start_index = 1; 

    while (start_index < size)
    {
        int end_index = (start_index * 2 + 1 < size) ? start_index * 2 + 1 : size;

        for (int i = start_index; i < end_index; i++) 
        {
            int is_left = (i % 2 == 1); 
            int parent_index = is_left ? (i - 1) / 2 : (i - 2) / 2;
            int parent_value = arr[parent_index];

            print_pyramid_element(level, parent_value, 0, is_left, arr[i]);
        }
        level++;
        start_index = start_index * 2 + 1;
    }
}

void print_array(int arr[], int size) 
{
    printf("Исходный массив: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() 
{
    setlocale(LC_ALL, "RUS");

    // Тест 1
    int arr1[] = { 1, 3, 6, 5, 9, 8 };
    int size1 = 6;

    print_array(arr1, size1);
    printf("Пирамида:\n");
    print_pyramid(arr1, size1);
    printf("\n");

    // Тест 2
    int arr2[] = { 94, 67, 18, 44, 55, 12, 6, 42 };
    int size2 = 8;

    print_array(arr2, size2);
    printf("Пирамида:\n");
    print_pyramid(arr2, size2);
    printf("\n");

    // Тест 3
    int arr3[] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
    int size3 = 10;

    print_array(arr3, size3);
    printf("Пирамида:\n");
    print_pyramid(arr3, size3);

    return 0;
}