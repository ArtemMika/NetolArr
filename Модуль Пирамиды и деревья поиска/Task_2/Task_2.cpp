#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

void print_array(int arr[], int size)
{
    printf("Исходный массив: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_pyramid_element(int level, int parent_value, int is_root, int is_left, int value)
{
    if (is_root)
    {
        printf("%d корень %d", level, value);
    }
    else if (is_left)
    {
        printf("%d левый(%d) %d", level, parent_value, value);
    }
    else
    {
        printf("%d правый(%d) %d", level, parent_value, value);
    }
}

void print_pyramid(int arr[], int size)
{
    printf("Пирамида:\n");
    if (size == 0) return;

    print_pyramid_element(0, 0, 1, 0, arr[0]);
    printf("\n");

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
            printf("\n");
        }
        level++;
        start_index = start_index * 2 + 1;
    }
}

bool get_left_child_index(int current_index, int size, int* child_index)
{
    *child_index = current_index * 2 + 1;
    return *child_index < size;
}

bool get_right_child_index(int current_index, int size, int* child_index)
{
    *child_index = current_index * 2 + 2;
    return *child_index < size;
}

bool get_parent_index(int current_index, int* parent_index)
{
    if (current_index == 0)
    {
        return false;
    }
    *parent_index = (current_index - 1) / 2;
    return true;
}

int get_level(int index)
{
    int level = 0;
    while ((1 << level) - 1 <= index)
    {
        level++;
    }
    return level - 1;
}

int main()
{
    setlocale(LC_ALL, "RUS");

    int test_pyramids[][10] =
    {
        {1, 3, 6, 5, 9, 8},
        {94, 67, 18, 44, 55, 12, 6, 42},
        {16, 11, 9, 10, 5, 6, 8, 1, 2, 4}
    };
    int sizes[] = { 6, 8, 10 };

    for (int test_num = 0; test_num < 3; test_num++)
    {
        int* arr = test_pyramids[test_num];
        int size = sizes[test_num];

        print_array(arr, size);
        print_pyramid(arr, size);

        int current_index = 0;

        char command[10];

        do {
            int level = get_level(current_index);
            int parent_value = 0;
            int is_root = (current_index == 0);
            int is_left = !is_root && (current_index % 2 == 1);

            if (!is_root)
            {
                int parent_idx;
                get_parent_index(current_index, &parent_idx);
                parent_value = arr[parent_idx];
            }

            printf("Вы находитесь здесь: ");
            print_pyramid_element(level, parent_value, is_root, is_left, arr[current_index]);
            printf("\n");

            printf("Введите команду: ");
            scanf("%s", command);

            if (strcmp(command, "up") == 0)
            {
                int parent_index;
                if (get_parent_index(current_index, &parent_index))
                {
                    current_index = parent_index;
                    printf("Ок\n");
                }
                else
                {
                    printf("Ошибка! Отсутствует родитель\n");
                }
            }
            else if (strcmp(command, "left") == 0)
            {
                int child_index;
                if (get_left_child_index(current_index, size, &child_index))
                {
                    current_index = child_index;
                    printf("Ок\n");
                }
                else
                {
                    printf("Ошибка! Отсутствует левый потомок\n");
                }
            }
            else if (strcmp(command, "right") == 0)
            {
                int child_index;
                if (get_right_child_index(current_index, size, &child_index)) {
                    current_index = child_index;
                    printf("Ок\n");
                }
                else
                {
                    printf("Ошибка! Отсутствует правый потомок\n");
                }
            }
            else if (strcmp(command, "exit") == 0)
            {
                printf("\n");
            }
            else {
                printf("Ошибка! Неизвестная команда\n");
            }
        } while (strcmp(command, "exit") != 0);

        if (test_num < 2)
        {
            printf("\n--- Следующий тест ---\n\n");
        }
    }

    return 0;
}