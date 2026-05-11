#include <iostream>
#include <vector>
#include <utility> // для std::pair

template<typename T>
class Table 
{
private:
    std::vector<T> data;
    size_t rows;
    size_t cols;

public:
    Table(size_t r, size_t c) : rows(r), cols(c) 
    {
        data.resize(rows * cols);
    }

    T* operator[](size_t row)
    {
        return &data[row * cols];
    }

    const T* operator[](size_t row) const 
    {
        return &data[row * cols];
    }

    std::pair<size_t, size_t> Size() const 
    {
        return std::make_pair(rows, cols);
    }
};

int main() 
{
    auto test = Table<int>(2, 3);

    test[0][0] = 4;

    std::cout << test[0][0] << std::endl;

    for (size_t i = 0; i < test.Size().first; ++i)
    {
        for (size_t j = 0; j < test.Size().second; ++j) 
        {
            test[i][j] = static_cast<int>(i * test.Size().second + j);
            std::cout << test[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}