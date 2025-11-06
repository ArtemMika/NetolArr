#pragma once
#include <utility>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept> // для std::invalid_argument

template <typename T>
class ExtArray
{
private:
    std::vector<T> extended_array;
    size_t _size;
public:
    ExtArray(std::initializer_list<T> l) : extended_array(l)
    {
        _size = l.size();
    }

    ExtArray(int size) : _size(size)
    {
        extended_array.resize(_size);
    }

    T& operator[](size_t index)
    {
        return extended_array[index];
    }

    size_t size()
    {
        return _size;
    }

    double mean()
    {
        if (_size == 0) return 0;
        double sum = 0;
        for (size_t i = 0; i < _size; i++)
        {
            sum += extended_array[i];
        }
        return sum / _size;
    }

    double mean(size_t start, size_t end)
    {
        if (start >= end || start >= _size || end > _size) {
            throw std::invalid_argument("Неверный диапазон");
        }

        double sum = 0;
        for (size_t i = start; i < end; i++) {
            sum += extended_array[i];
        }
        return sum / (end - start);
    }

    double median()
    {
        if (_size == 0) return 0;
        std::vector<T> temp_array;
        std::copy(extended_array.begin(), extended_array.end(), std::back_inserter(temp_array));
        std::sort(temp_array.begin(), temp_array.end());
        if (_size % 2 == 1)
        {
            return temp_array[_size / 2];
        }
        else
        {
            return static_cast<double>(temp_array[(_size / 2) - 1] + temp_array[_size / 2]) / 2;
        }
    }

    std::pair<T, int> mode()
    {
        if (_size == 0) return { 0, 0 };
        T max = extended_array[0], cmax = 0, rmax = 0;
        for (int i = 0; i < _size; i++)
        {
            if (cmax > rmax)
            {
                rmax = cmax;
                max = extended_array[i - 1];
            }
            cmax = 0;
            for (int j = i; j < _size; j++)
            {
                if (extended_array[j] == extended_array[i])
                {
                    cmax++;
                }
            }
        }
        return { max, rmax };
    }
};

#include <cassert>

void testEmptyArray() 
{
    ExtArray<int> emptyArray(0);

    // Проверка размера
    assert(emptyArray.size() == 0);

    // Проверка mean()
    assert(emptyArray.mean() == 0);

    // Проверка median()
    assert(emptyArray.median() == 0);

    // Проверка mode()
    auto modeResult = emptyArray.mode();
    assert(modeResult.first == 0);
    assert(modeResult.second == 0);
}
void testMeanRange() 
{
    ExtArray<int> array({ 1, 2, 3, 4, 5 });

    // Валидные тесты
    try 
    {
        // Проверка среднего для всего массива
        assert(array.mean(0, 5) == 3.0);

        // Проверка среднего для части массива
        assert(array.mean(1, 4) == 3.0);  // (2 + 3 + 4) / 3 = 3

        // Проверка граничных значений
        assert(array.mean(0, 1) == 1.0);
        assert(array.mean(4, 5) == 5.0);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка в валидных тестах: " << e.what() << std::endl;
    }

    // Тесты с некорректными диапазонами
    try 
    {
        // Неверный порядок индексов
        array.mean(5, 0);
        assert(false);  // Должны были выбросить исключение
    }
    catch (const std::invalid_argument&) {
        assert(true);
    }

    try 
    {
        // Выход за пределы массива
        array.mean(2, 6);
        assert(false);
    }
    catch (const std::invalid_argument&) {
        assert(true);
    }

    try
    {
        // Нулевой диапазон
        array.mean(3, 3);
        assert(false);
    }
    catch (const std::invalid_argument&) {
        assert(true);
    }

    try 
    {
        // Отрицательные индексы
        array.mean(-1, 2);
        assert(false);
    }
    catch (const std::invalid_argument&) {
        assert(true);
    }
}

int main() 
{
    try 
    {
        testEmptyArray();
        testMeanRange();

        std::cout << "Все тесты пройдены успешно!" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}