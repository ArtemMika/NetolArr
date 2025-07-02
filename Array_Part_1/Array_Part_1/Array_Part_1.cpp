#include <iostream> 

int main() {

    int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    int size = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < size; i++) {
    
        std::cout << numbers[i];

        if (i < size - 1) {
            std::cout << ", ";
        }
    }

    std::cout << std::endl;

    return 0;
}