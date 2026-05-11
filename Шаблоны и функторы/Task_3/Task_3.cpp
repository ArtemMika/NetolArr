#include <iostream>
#include <vector>
#include <algorithm>

class DivisibleByThreeCounter 
{
private:
    int sum;
    int count;

public:
    DivisibleByThreeCounter() : sum(0), count(0) {}

    void operator()(int num) 
    {
        if (num % 3 == 0)
        {
            sum += num;
            count++;
        }
    }

    int get_sum() const 
    {
        return sum;
    }

    int get_count() const 
    {
        return count;
    }

    friend int get_sum(const DivisibleByThreeCounter& counter);
    friend int get_count(const DivisibleByThreeCounter& counter);
};

int get_sum(const DivisibleByThreeCounter& counter) 
{
    return counter.sum;
}

int get_count(const DivisibleByThreeCounter& counter) 
{
    return counter.count;
}

int main() 
{
    std::vector<int> numbers = { 4, 1, 3, 6, 25, 54 };

    DivisibleByThreeCounter counter;

    std::for_each(numbers.begin(), numbers.end(), counter);

    std::cout << "[OUT]: get_sum() = " << get_sum(counter) << std::endl;
    std::cout << "[OUT]: get_count() = " << get_count(counter) << std::endl;

    return 0;
}