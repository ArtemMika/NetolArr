#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <cstddef>
#include <atomic>

// Функция для параллельного сложения векторов
void vector_add_range(const std::vector<double>& a,
    const std::vector<double>& b,
    std::vector<double>& c,
    size_t start,
    size_t end) 
{
    for (size_t i = start; i < end; ++i) 
    {
        c[i] = a[i] + b[i];
    }
}

// Запуск сложения с заданным числом потоков
double run_with_threads(const std::vector<double>& a,
    const std::vector<double>& b,
    std::vector<double>& c,
    unsigned int num_threads) 
{
    const size_t n = a.size();
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    const size_t chunk_size = (n + num_threads - 1) / num_threads; // округление вверх

    auto start_time = std::chrono::high_resolution_clock::now();

    for (unsigned int t = 0; t < num_threads; ++t)
    {
        size_t start = t * chunk_size;
        size_t end = std::min(start + chunk_size, n);
        if (start >= n) break;

        threads.emplace_back(vector_add_range,
            std::ref(a), std::ref(b), std::ref(c),
            start, end);
    }

    for (auto& th : threads)
    {
        th.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;
    return diff.count();
}

int main() 
{
    // Вывод количества аппаратных ядер
    unsigned int hw_threads = std::thread::hardware_concurrency();
    if (hw_threads == 0) hw_threads = 1; // если не удалось определить
    std::cout << "Количество аппаратных ядер - " << hw_threads << "\n\n";

    std::vector<size_t> sizes = { 1000, 10000, 100000, 1000000 };
    std::vector<unsigned int> thread_counts = { 1, 2, 4, 8, 16 };

    std::cout << std::setw(10) << "Размер";
    for (unsigned int t : thread_counts) 
    {
        std::cout << std::setw(12) << t << " потоков";
    }
    std::cout << "\n";

    // Тестирование для каждого размера
    for (size_t n : sizes)
    {
        std::vector<double> a(n, 1.0);
        std::vector<double> b(n, 2.0);
        std::vector<double> c(n, 0.0);

        std::cout << std::setw(10) << n;

        for (unsigned int t : thread_counts) 
        {
            double time_sec = run_with_threads(a, b, c, t);
            std::cout << std::setw(12) << std::fixed << std::setprecision(6) << time_sec << "s";
        }
        std::cout << "\n";
    }

    return 0;
}