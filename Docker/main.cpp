#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main()
 {
    std::set<int, std::greater<int>> unique_sorted;
    int x;

    while (std::cin >> x)
 {
        unique_sorted.insert(x);
    }

    for (int v : unique_sorted) 
{
        std::cout << v << "\n";
    }
    return 0;
}