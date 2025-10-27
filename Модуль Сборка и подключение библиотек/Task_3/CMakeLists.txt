cmake_minimum_required(VERSION 3.16)
project(Task_3)

# Настройка компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Создание библиотеки
add_library(LeaverLib SHARED
    Library/leaver.cpp
)

# Настройка путей включения для библиотеки
target_include_directories(LeaverLib PUBLIC
    ${CMAKE_SOURCE_DIR}/Library
)

# Создание исполняемого файла
add_executable(Task_3
    out/Task_3.cpp  # Убедитесь, что путь указан правильно
)

# Связывание библиотеки с приложением
target_link_libraries(Task_3 PRIVATE LeaverLib)

# Настройка путей включения для приложения
target_include_directories(Task_3 PUBLIC
    ${CMAKE_SOURCE_DIR}/Library
)

# Настройки для Windows
if(WIN32)
    set_target_properties(LeaverLib PROPERTIES
        WIN32_EXECUTABLE TRUE
        DEBUG_POSTFIX d
    )
endif()