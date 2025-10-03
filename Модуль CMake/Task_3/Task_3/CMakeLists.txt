cmake_minimum_required(VERSION 3.10)
project(Task_2)

# Указываем директорию с заголовочными файлами
include_directories(${CMAKE_SOURCE_DIR}/Файлы заголовков)

# Собираем исполняемый файл
add_executable(Task_2
    Исходные файлы/main.cpp
    Исходные файлы/figure.cpp
    Исходные файлы/triangle.cpp
    Исходные files/right_triangle.cpp
    Исходные files/rectangle.cpp
    Исходные files/square.cpp
    Исходные files/parallelogram.cpp
    Исходные files/rhombus.cpp
    Исходные files/geometry_error.cpp
)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")