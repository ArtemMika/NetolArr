#include <iostream>
#include <locale>

using namespace std;

void print_dynamic_array(int* arr, int logical_size, int actual_size) 
{
    cout << "Динамический массив: ";
    for (int i = 0; i < actual_size; ++i) 
    {
        if (i < logical_size) 
        {
            cout << arr[i];
        }
        else
        {
            cout << "_";
        }
        if (i < actual_size - 1) 
        {
            cout << " ";
        }
    }
    cout << endl;
}

int* append_to_dynamic_array(int* arr, int& logical_size, int& actual_size, int new_element) 
{
    if (logical_size < actual_size) 
    {
        arr[logical_size] = new_element;
        logical_size++;
        return arr;
    }

    int new_actual_size = actual_size * 2;
    int* new_arr = new int[new_actual_size];

    for (int i = 0; i < logical_size; ++i)
    {
        new_arr[i] = arr[i];
    }

    new_arr[logical_size] = new_element;

    logical_size++;
    actual_size = new_actual_size;

    delete[] arr;

    return new_arr;
}

int main() 
{
    if (!setlocale(LC_ALL, ""))
    {
        setlocale(LC_ALL, "");
    }

    int actual_size, logical_size;

    cout << "Введите фактический размер массива: ";
    cin >> actual_size;

    cout << "Введите логический размер массива: ";
    cin >> logical_size;

    while (logical_size > actual_size)
    {
        cout << "Ошибка! Логический размер массива не может превышать фактический!" << endl;
        cout << "Введите фактический размер массива: ";
        cin >> actual_size;
        cout << "Введите логический размер массива: ";
        cin >> logical_size;
    }

    int* arr = new int[actual_size];

    for (int i = 0; i < logical_size; ++i) 
    {
        cout << "Введите arr[" << i << "]: ";
        cin >> arr[i];
    }

    print_dynamic_array(arr, logical_size, actual_size);

    int new_element;

    do {
        cout << "Введите элемент для добавления: ";
        cin >> new_element;

        if (new_element != 0)
        {
            arr = append_to_dynamic_array(arr, logical_size, actual_size, new_element);
            print_dynamic_array(arr, logical_size, actual_size);
        }
    } while (new_element != 0);

    cout << "Спасибо! Ваш массив: ";
    print_dynamic_array(arr, logical_size, actual_size);

    delete[] arr;

    return 0;
}