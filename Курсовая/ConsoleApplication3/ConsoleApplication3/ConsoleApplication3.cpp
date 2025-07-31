#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> // для sleep
#ifdef _WIN32
#include <windows.h> // для Windows
#else
#include <unistd.h> // для Unix/Linux
#endif

const std::string file_name = "data.txt";
const int MAX_INIT_CELLS_COUNT = 1000;

const int CRITICAL_COUNT_OF_GENERATIONS = 1000;

const std::string CELLS_DEAD_MSG = "All cells are dead. Game over";
const std::string WORLD_STAGNATED_MSG = "The world has stagnated. Game over";

const char NULL_CHAR = static_cast<char>(0);
const char DEAD_CELL = '-';
const char LIVE_CELL = '*';

// Функция задержки
void sleep_ms(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

// Функция получения числа из файла
int get_number(std::ifstream& file_data) {
    std::string buffer_string = "";
    file_data >> buffer_string;
    try {
        return std::stoi(buffer_string);
    }
    catch (std::invalid_argument error) {
        std::cout << "Ошибка при получении числа из строки: " << buffer_string << std::endl;
        throw std::logic_error("Не удалось обработать входящие значения");
    }
}

// Очистка памяти
template <typename T>
void delete_data(T** data, int size) {
    for (int i = 0; i < size; i++) {
        delete data[i];
        data[i] = nullptr;
    }
    delete data;
}

// Создание игрового поля
char** create_canvas(int rows, int cols) {
    char** canvas = new char* [rows];
    for (int r = 0; r < rows; r++) {
        canvas[r] = new char[cols];
        std::fill_n(canvas[r], cols, DEAD_CELL);
    }
    return canvas;
}

// Инициализация поля начальными данными
void init_canvas(char** canvas, int rows, int cols, int** data, int cells) {
    for (int i = 0; i < cells; i++) {
        const int r = data[i][0];
        const int c = data[i][1];
        canvas[r][c] = LIVE_CELL;
    }
}

// Вывод поля на экран
void print_canvas(char** canvas, int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            std::cout << canvas[r][c];
            if (c < cols - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Получение значения клетки с проверкой границ
char get_cell(char** canvas, int r, int c, int rows, int cols) {
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        return NULL_CHAR;
    }
    return canvas[r][c];
}

// Подсчет живых соседей
int get_live_neighbours(char** canvas, int r, int c, int rows, int cols) {
    int live_neighbours = 0;
    // Проверяем всех соседей
    get_cell(canvas, r - 1, c, rows, cols) == LIVE_CELL && ++live_neighbours;
    get_cell(canvas, r - 1, c - 1, rows, cols) == LIVE_CELL && ++live_neighbours;
    get_cell(canvas, r - 1, c + 1, rows, cols) == LIVE_CELL && ++live_neighbours;
    get_cell(canvas, r + 1, c, rows, cols) == LIVE_CELL && ++live_neighbours;
    get_cell(canvas, r + 1, c - 1, rows, cols) == LIVE_CELL && ++live_neighbours;
    get_cell(canvas, r + 1, c + 1, rows, cols) == LIVE_CELL && ++live_neighbours;
    get_cell(canvas, r, c - 1, rows, cols) == LIVE_CELL && ++live_neighbours;
    get_cell(canvas, r, c + 1, rows, cols) == LIVE_CELL && ++live_neighbours;

    return live_neighbours;
}

// Проверка необходимости возрождения клетки
bool should_revive_cell(char cell, int live_neighbours) {
    return cell == DEAD_CELL && live_neighbours == 3;
}

// Проверка необходимости уничтожения клетки
bool should_kill_cell(char cell, int live_neighbours) {
    return cell == LIVE_CELL && (live_neighbours < 2 || live_neighbours > 3);
}

// Создание нового поколения
char** update_generation(char** canvas, int rows, int cols) {
    char** new_canvas = create_canvas(rows, cols);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            const char current_cell = canvas[r][c];
            const int live_neighbours = get_live_neighbours(canvas, r, c, rows, cols);

            if (should_revive_cell(current_cell, live_neighbours)) {
                new_canvas[r][c] = LIVE_CELL;
            }
            else if (should_kill_cell(current_cell, live_neighbours)) {
                new_canvas[r][c] = DEAD_CELL;
            }
            else {
                new_canvas[r][c] = current_cell;
            }
        }
    }

    return new_canvas;
}

// Вывод информации о поколении
void print_generation_info(int generation, int alive_cells) {
    std::cout << "Поколение: " << generation << ". Живых клеток: " << alive_cells << std::endl;
}

// Подсчет живых клеток на поле
int count_alive_cells(char** canvas, int rows, int cols) {
    int live_cells = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (canvas[r][c] == LIVE_CELL) {
                ++live_cells;
            }
        }
    }

    return live_cells;
}

// Сравнение двух полей
bool get_canvas_has_changes(char** canvas_a, char** canvas_b, int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (canvas_a[r][c] != canvas_b[r][c]) {
                return true;
            }
        }
    }
    return false;
}

// Основная функция игры
void core(char** canvas, int rows, int cols, int init_cells) {
    char** new_canvas = canvas;
    int generation = 1;

    // Первый рендер
    print_canvas(canvas, rows, cols);
    print_generation_info(generation, init_cells);
    std::cout << std::endl;
    sleep_ms(1000);

    while (++generation < CRITICAL_COUNT_OF_GENERATIONS) {
        new_canvas = update_generation(canvas, rows, cols);

        const bool has_changes = get_canvas_has_changes(canvas, new_canvas, rows, cols);
        const int alive_cells = count_alive_cells(new_canvas, rows, cols);

        delete_data<char>(canvas, rows);
        canvas = nullptr;

        std::system("clear");
        print_canvas(new_canvas, rows, cols);
        print_generation_info(generation, alive_cells);

        if (!has_changes || alive_cells == 0) {
            const std::string message = has_changes ? CELLS_DEAD_MSG : WORLD_STAGNATED_MSG;
            std::cout << message << std::endl;
            break;
        }

        canvas = new_canvas;
        std::cout << std::endl;
        sleep_ms(1000);
    }

    delete_data<char>(new_canvas, rows);
    new_canvas = nullptr;
}

int main() 
{
    setlocale(LC_ALL, "rus");
    std::system("clear");
    std::ifstream fs_data(static_cast<std::string>("./") + file_name);

    if (!fs_data.is_open()) {
        std::cout << "[ERROR]: Файл (" << file_name << ") не найден!" << std::endl;
        fs_data.close();
        exit(1);
    }

    int init_cells_count = 0;
    int** init_cells = new int* [MAX_INIT_CELLS_COUNT];

    try {
        const int rows = get_number(fs_data);
        const int cols = get_number(fs_data);

        while (!fs_data.eof()) {
            if (init_cells_count >= MAX_INIT_CELLS_COUNT) {
                break;
            }
            const int x = get_number(fs_data);
            const int y = get_number(fs_data);

            init_cells[init_cells_count] = new int[2];
            init_cells[init_cells_count][0] = x;
            init_cells[init_cells_count][1] = y;
            init_cells_count++;
        }

        fs_data.close();

        char** canvas = create_canvas(rows, cols);
        init_canvas(canvas, rows, cols, init_cells, init_cells_count);

        core(canvas, rows, cols, init_cells_count);

        delete_data<int>(init_cells, init_cells_count);
        init_cells = nullptr;
        canvas = nullptr;
    }
    catch (std::logic_error logic_error) {
        std::cout << logic_error.what() << std::endl;
        delete_data(init_cells, init_cells_count);
        init_cells = nullptr;
        exit(2);
    }
    catch (...) {
        std::cout << "Необработанная ошибка." << std::endl;
        delete_data(init_cells, init_cells_count);
        init_cells = nullptr;
        exit(3);
    }

    return 0;
}