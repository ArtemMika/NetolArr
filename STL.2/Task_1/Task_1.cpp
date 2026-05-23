#include <iostream>
#include <vector>
#include <algorithm>

void removeDuplicates(std::vector<int>& vec) 
{
    std::sort(vec.begin(), vec.end());

    auto last = std::unique(vec.begin(), vec.end());

    vec.erase(last, vec.end());
}

int main() 
{
    std::vector<int> data = { 1, 1, 2, 5, 6, 1, 2, 4 };

    std::cout << "До удаления дубликатов: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    removeDuplicates(data);

    std::cout << "После удаления дубликатов: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}