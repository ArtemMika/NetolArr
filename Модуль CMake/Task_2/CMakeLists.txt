cmake_minimum_required(VERSION 3.10)
project(Task_2)

# Настройка кодировки UTF-8
if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=UTF-8)
endif()

# Указываем директории с исходниками и заголовками
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(HEADER_DIR "${CMAKE_SOURCE_DIR}/include")

# Собираем список исходных файлов
file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.cpp"
)

# Добавляем директории включения
include_directories(${HEADER_DIR})

# Создаем исполняемый файл
add_executable(Task_2
    ${SOURCES}
    main.cpp
)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Настройки для Windows
if(WIN32)
    set_target_properties(Task_2 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()