#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <chrono>

const size_t MIN_BLOCK_SIZE = 1000;

template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) 
{
    auto size = std::distance(first, last);

    if (size <= MIN_BLOCK_SIZE) 
    {
        std::for_each(first, last, f);
        return;
    }

    Iterator mid = first + size / 2;

    auto left = std::async(
        std::launch::async,
        parallel_for_each<Iterator, Func>,
        first, mid, f
    );

    parallel_for_each(mid, last, f);

    left.wait();
}

int main() 
{
    const size_t N = 10'000'000;
    std::vector<int> data(N);

    for (size_t i = 0; i < N; ++i) 
    {
        data[i] = static_cast<int>(i);
    }

    auto f = [](int& x) { x *= 2; };

    auto start = std::chrono::high_resolution_clock::now();
    parallel_for_each(data.begin(), data.end(), f);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Параллельный for_each: " << duration.count() << " мс\n";

    bool correct = true;
    for (size_t i = 0; i < N; ++i)
    {
        if (data[i] != static_cast<int>(i * 2)) 
        {
            correct = false;
            break;
        }
    }
    std::cout << (correct ? "OK" : "FAIL") << "\n";

    std::vector<int> data2(N);
    for (size_t i = 0; i < N; ++i) 
    {
        data2[i] = static_cast<int>(i);
    }

    start = std::chrono::high_resolution_clock::now();
    std::for_each(data2.begin(), data2.end(), f);
    end = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Последовательный for_each: " << duration.count() << " мс\n";

    return 0;
}