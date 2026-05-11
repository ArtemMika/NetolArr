#include <iostream>
#include <vector>

template<typename T>
T square(T value) 
{
    return value * value;
}

template<typename T>
std::vector<T> square(const std::vector<T>& vec) 
{
    std::vector<T> result;
    result.reserve(vec.size());

    for (const auto& element : vec)
    {
        result.push_back(element * element);
    }

    return result;
}

template<typename T>
void printResult(const T& result) 
{
    if constexpr (std::is_same_v<T, std::vector<typename T::value_type>>) 
    {
        std::cout << "[";
        for (size_t i = 0; i < result.size(); ++i)
        {
            std::cout << result[i];
            if (i < result.size() - 1) 
            {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
    else 
    {
        std::cout << result << "\n";
    }
}

int main()
{
    //простое число
    int num = 4;
    auto result1 = square(num);
    std::cout << "[IN]: " << num << "\n";
    std::cout << "[OUT]: ";
    printResult(result1);

    //вектор
    std::vector<int> vec = { -1, 4, 8 };
    auto result2 = square(vec);
    std::cout << "[IN]: ";
    printResult(vec);
    std::cout << "[OUT]: ";
    printResult(result2);

    return 0;
}