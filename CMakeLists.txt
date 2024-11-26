# Минимальная версия CMake
cmake_minimum_required(VERSION 3.14)

# Название проекта
project(EqvilentCpp LANGUAGES CXX)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка папок для сборки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Исходные файлы (исключаем test.cpp)
file(GLOB SRC_FILES src/*.cpp)

# Добавляем основное приложение
add_executable(main ${SRC_FILES})

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# Скачиваем и подключаем Google Test
FetchContent_MakeAvailable(googletest)

# Включаем поддержку тестов
enable_testing()

# Тестовый исполняемый файл
add_executable(tests tests/tests.cpp src/task.cpp)

# Линковка тестов с Google Test
target_link_libraries(tests gtest gtest_main)

# Добавляем тесты
add_test(NAME AllTests COMMAND tests)
