#include <sstream>  // Добавляем эту строку
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <algorithm>
#include <cctype>

// Константы
const std::string FILE_NAME = "data.txt";
const int MAX_INIT_CELLS_COUNT = 1000;
const int CRITICAL_COUNT_OF_GENERATIONS = 1000;
const std::string CELLS_DEAD_MSG = "Все клетки умерли. Игра окончена";
const std::string WORLD_STAGNATED_MSG = "Мир стабилизировался. Игра окончена";
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

// Создание файла через консоль
void createWorldFromConsole() {
    std::ofstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка при создании файла!" << std::endl;
        return;
    }

    // Ввод размеров поля
    int rows, cols;
    std::cout << "Введите размеры игрового поля:" << std::endl;
    std::cout << "Количество строк: ";
    if (!(std::cin >> rows)) {
        std::cerr << "Ошибка: некорректный ввод размеров поля!" << std::endl;
        return;
    }

    std::cout << "Количество столбцов: ";
    if (!(std::cin >> cols)) {
        std::cerr << "Ошибка: некорректный ввод размеров поля!" << std::endl;
        return;
    }

    // Очищаем буфер ввода
    std::cin.ignore();

    // Проверка корректности размеров
    if (rows <= 0 || cols <= 0) {
        std::cerr << "Ошибка: размеры поля должны быть положительными!" << std::endl;
        return;
    }

    file << rows << " " << cols << std::endl;

    // Ввод координат живых клеток
    std::cout << "\nВведите координаты живых клеток (x y):" << std::endl;
    std::cout << "Для завершения ввода введите 'end'" << std::endl;

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "end") {
            break;
        }

        std::istringstream iss(input);
        int x, y;

        // Проверяем корректность ввода
        if (iss >> x >> y) {
            // Проверяем границы
            if (x >= 0 && x < rows && y >= 0 && y < cols) {
                file << x << " " << y << std::endl;
            }
            else {
                std::cout << "Ошибка: координаты (" << x << ", " << y << ") выходят за границы поля!" << std::endl;
            }
        }
        else {
            std::cout << "Ошибка: неверный формат ввода! Введите два числа через пробел" << std::endl;
        }
    }

    file.close();
    std::cout << "\nФайл data.txt успешно создан!" << std::endl;
}

// Функция чтения числа из файла с улучшенной обработкой
int get_number(std::ifstream& file_data) {
    std::string buffer_string;
    file_data >> buffer_string;

    // Проверяем, что строка не пустая
    if (buffer_string.empty()) {
        throw std::logic_error("Пустая строка в файле");
    }

    // Очищаем строку от лишних пробелов и символов
    buffer_string.erase(std::remove_if(buffer_string.begin(), buffer_string.end(), isspace), buffer_string.end());

    try {
        return std::stoi(buffer_string);
    }
    catch (const std::invalid_argument&) {
        std::cerr << "Ошибка: некорректное число в файле: " << buffer_string << std::endl;
        throw std::logic_error("Ошибка при чтении числа");
    }
    catch (const std::out_of_range&) {
        std::cerr << "Ошибка: число выходит за допустимый диапазон: " << buffer_string << std::endl;
        throw std::logic_error("Ошибка при чтении числа");
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

        system("cls");
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

int main() {
    system("cls");

    setlocale(LC_ALL, "rus");

    // Выбор режима игры
    std::cout << "Выберите режим игры:\n"
        << "1. Создать новый мир\n"
        << "2. Загрузить существующий мир\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        createWorldFromConsole();
    }

    std::ifstream fs_data("data.txt");
    if (!fs_data.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл data.txt\n";
        return 1;
    }

    // Проверяем, что файл не пустой
    if (fs_data.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Ошибка: файл data.txt пустой\n";
        return 1;
    }

    // Очищаем буфер файла
    fs_data.clear();
    fs_data.seekg(0);

    try {
        // Читаем размеры поля
        int rows = get_number(fs_data);
        int cols = get_number(fs_data);

        // Проверяем корректность размеров
        if (rows <= 0 || cols <= 0) {
            throw std::logic_error("Некорректные размеры поля");
        }

        // Читаем координаты клеток
        int init_cells_count = 0;
        int** init_cells = new int* [MAX_INIT_CELLS_COUNT];

        std::string line;
        while (std::getline(fs_data, line)) {
            std::istringstream iss(line);
            int x, y;

            if (init_cells_count >= MAX_INIT_CELLS_COUNT) {
                break;
            }

            if (iss >> x >> y) {
                // Проверяем корректность координат
                if (x >= 0 && x < rows && y >= 0 && y < cols) {
                    init_cells[init_cells_count] = new int[2];
                    init_cells[init_cells_count][0] = x;
                    init_cells[init_cells_count][1] = y;
                    init_cells_count++;
                }
                else {
                    std::cerr << "Ошибка: некорректные координаты (" << x << ", " << y << ")\n";
                }
            }
        }

        // Создаем и инициализируем канвас
        char** canvas = create_canvas(rows, cols);
        init_canvas(canvas, rows, cols, init_cells, init_cells_count);

        // Запускаем основную игру
        core(canvas, rows, cols, init_cells_count);

        // Освобождаем память
        for (int i = 0; i < init_cells_count; i++) {
            delete[] init_cells[i];
        }
        delete[] init_cells;
        delete_data<char>(canvas, rows);
    }
    catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}