# LeaverLibrary/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(LeaverLibrary)

# Определяем исходные файлы библиотеки
set(LIBRARY_SOURCES
    Leaver.cpp
    Leaver.h
)

# Создаем динамическую библиотеку
add_library(Leaver SHARED ${LIBRARY_SOURCES})

# Определяем макрос для экспорта символов
set_target_properties(Leaver PROPERTIES
    COMPILE_DEFINITIONS "LEAVERLIB_EXPORTS"
)

# Настраиваем include директории
target_include_directories(Leaver PUBLIC
    $
)

# Настройки для Windows
if(WIN32)
    set_target_properties(Leaver PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()