#include <iostream>
#include <set>

using namespace std;

int main() 
{
    int n;
    cin >> n;

    set<int, greater<int>> uniqueNumbers;

    for (int i = 0; i < n; ++i) 
    {
        int number;
        cin >> number;
        uniqueNumbers.insert(number);
    }

    cout << "[OUT]:" << endl;
    for (const auto& num : uniqueNumbers) 
    {
        cout << num << endl;
    }

    return 0;
}