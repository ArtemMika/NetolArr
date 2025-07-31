#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

// Глобальные переменные
vector<vector<bool>> grid;
vector<vector<bool>> prevGrid;
int rows = 0;
int cols = 0;
int generation = 0;
int cells = 0;

// Функция очистки консоли
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Функция чтения файла
bool readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл!" << endl;
        return false;
    }

    file >> rows >> cols;
    if (rows <= 0 || cols <= 0) {
        cout << "Ошибка: некорректные размеры поля!" << endl;
        return false;
    }

    grid.assign(rows, vector<bool>(cols, false));
    prevGrid = grid;

    int x, y;
    while (file >> x >> y) {
        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            grid[x][y] = true;
            cells++;
        }
    }
    return true;
}

// Подсчет живых соседей
int countNeighbors(int x, int y) {
    int count = 0;
    for (int i = max(0, x - 1); i <= min(rows - 1, x + 1); i++) {
        for (int j = max(0, y - 1); j <= min(cols - 1, y + 1); j++) {
            if (i == x && j == y) continue;
            if (grid[i][j]) count++;
        }
    }
    return count;
}

// Обновление состояния поля
void update() {
    prevGrid = grid;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = countNeighbors(i, j);
            if (grid[i][j]) {
                if (neighbors < 2 || neighbors > 3) {
                    grid[i][j] = false;
                }
            }
            else {
                if (neighbors == 3) {
                    grid[i][j] = true;
                }
            }
        }
    }
    generation++;
}

// Подсчет живых клеток
int countAlive() {
    int count = 0;
    for (const auto& row : grid) {
        for (bool cell : row) {
            if (cell) count++;
        }
    }
    return count;
}

// Вывод состояния поля
void print() {
    clearScreen();
    cout << "Поколение: " << generation << endl;
    cout << "Живых клеток: " << countAlive() << endl;

    for (const auto& row : grid) {
        for (bool cell : row) {
            cout << (cell ? '*' : '-') << ' ';
        }
        cout << endl;
    }
    cout << endl;

    this_thread::sleep_for(chrono::seconds(1));
}

// Проверка условий окончания игры
bool isGameOver() {
    return countAlive() == 0 || grid == prevGrid;
}

int main() {
    string filename = "input.txt";
    setlocale(LC_ALL, "rus");

    if (!readFile(filename)) {
        return 1;
    }

    do {
        print();
        update();
    } while (!isGameOver());

    print();
    cout << "Игра окончена! Причина: ";
    if (countAlive() == 0) {
        cout << "Все клетки умерли" << endl;
    }
    else {
        cout << "Конфигурация стабилизировалась" << endl;
    }

    cout << "Финальное поколение: " << generation << endl;
    cout << "Количество живых клеток: " << countAlive() << endl;

    return 0;
}