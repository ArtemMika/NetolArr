cmake_minimum_required(VERSION 3.20)
project(PgTest LANGUAGES CXX)

# Пути к PostgreSQL 18 (прямые слеши / обязательны для CMake)
set(PG_INCLUDE_DIR "C:/Program Files/PostgreSQL/18/include")
set(PG_LIB_DIR "C:/Program Files/PostgreSQL/18/lib")

# Подключаем папки с заголовками и библиотеками
include_directories(${PG_INCLUDE_DIR})
link_directories(${PG_LIB_DIR})

add_executable(PgTest main.cpp)

# Линкуем библиотеку libpq.lib
target_link_libraries(PgTest PRIVATE libpq)
