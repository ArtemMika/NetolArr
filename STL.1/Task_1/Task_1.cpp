#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void countAndSortCharacters(const string& text)
{
    map<char, int> frequency;
    for (char c : text)
    {
        frequency[c]++;
    }

    vector<pair<char, int>> sortedFreq(frequency.begin(), frequency.end());

    sort(sortedFreq.begin(), sortedFreq.end(),
        [](const pair<char, int>& a, const pair<char, int>& b) 
        {
            return a.second > b.second;
        });

    cout << "[OUT]:" << endl;
    for (const auto& pair : sortedFreq) 
    {
        cout << pair.first << ": " << pair.second << endl;
    }
}

int main() 
{
    string input = "Hello world!!";
    cout << "[IN]: " << input << endl;
    countAndSortCharacters(input);

    return 0;
}