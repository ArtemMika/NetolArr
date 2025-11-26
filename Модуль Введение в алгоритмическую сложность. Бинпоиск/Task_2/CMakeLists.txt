cmake_minimum_required(VERSION 3.10)
project(CountGreaterElements)

# Настройка кодировки UTF-8
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка кодировки для Windows
if(WIN32)
    add_compile_options(/utf-8)
    add_link_options(/utf-8)
    # Настройка локали для корректного отображения русского текста
    add_definitions(-D_ENABLE_UNICODE -DUNICODE)
endif()

# Установка кодировки для других систем
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -finput-charset=UTF-8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8")

# Добавление исполняемого файла
add_executable(count_greater_elements main.cpp)