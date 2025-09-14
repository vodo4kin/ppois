cmake_minimum_required(VERSION 3.10)
project(Sets)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем папки с исходниками
include_directories(include)

# Основной исполняемый файл
add_executable(main_app
    src/main.cpp
    src/Sets.cpp
)

# Если хотите также собрать тесты (optional)
add_executable(tests_runner
    test/test.cpp
    src/Sets.cpp
)

find_package(GTest REQUIRED)
target_link_libraries(tests_runner GTest::GTest GTest::Main)