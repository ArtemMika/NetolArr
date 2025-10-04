# Task_3/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Task_3)

# Находим библиотеку
add_subdirectory(../LeaverLibrary)

# Определяем исходные файлы приложения
set(APP_SOURCES
    main.cpp
)

# Создаем исполняемый файл
add_executable(ConsoleApp ${APP_SOURCES})

# Настраиваем include директории
target_include_directories(ConsoleApp PUBLIC
    $
)

# Связываем приложение с библиотекой
target_link_libraries(ConsoleApp PRIVATE Leaver)

# Настройки для Windows
if(WIN32)
    set_target_properties(ConsoleApp PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()