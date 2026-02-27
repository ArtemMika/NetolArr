cmake_minimum_required(VERSION 3.10)
project(FibonacciNaive CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка кодировки для поддержки русского языка
if(WIN32)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=utf-8)
endif()

add_executable(fibonacci_naive fibonacci_naive.cpp)

if(WIN32)
    target_compile_definitions(fibonacci_naive PRIVATE _WIN32_WINNT=0x0A00)
endif()