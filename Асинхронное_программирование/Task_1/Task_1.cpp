#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <chrono>
#include <iomanip>

int find_min_index_async(const std::vector<int>& data, size_t start, size_t end) 
{
    if (start >= end) return static_cast<int>(start);

    size_t min_idx = start;
    for (size_t i = start + 1; i < end; ++i) 
    {
        if (data[i] < data[min_idx]) 
        {
            min_idx = i;
        }
    }
    return static_cast<int>(min_idx);
}

// promise-future
int get_min_index(const std::vector<int>& data, size_t start, size_t end)
{
    std::promise<int> pr;
    std::future<int> fut = pr.get_future();

    // Запуск
    std::thread([&pr, &data, start, end]() 
        {
        try {
            int result = find_min_index_async(data, start, end);
            pr.set_value(result);
        }
        catch (...) 
        {
            pr.set_exception(std::current_exception());
        }
        }).detach();

    return fut.get();
}

void selection_sort_with_async_min(std::vector<int>& arr) 
{
    const size_t n = arr.size();
    for (size_t i = 0; i + 1 < n; ++i) 
    {
        int min_idx = get_min_index(arr, i, n);

        if (min_idx != static_cast<int>(i)) 
        {
            std::swap(arr[i], arr[min_idx]);
        }
    }
}

int main() 
{
    std::vector<int> data = { 23, 1, 45, 3, 9, 17, 8, 60, 5 };

    std::cout << "Исходный массив: ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    selection_sort_with_async_min(data);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Отсортированный массив: ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n";

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Время сортировки: " << duration.count() << " мкс\n";

    return 0;
}