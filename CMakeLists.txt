cmake_minimum_required(VERSION 3.10)
project(PopTheBalloons)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Test Gui) # Добавляем Gui

set(CMAKE_AUTOMOC ON)

# Основное приложение
add_executable(PopTheBalloons
    main.cpp
    mainwindow.cpp
    mainwindow.h
    gameengine.cpp
    gameengine.h
    balloon.cpp
    balloon.h
)

target_link_libraries(PopTheBalloons Qt6::Core Qt6::Widgets Qt6::Gui) # Добавляем Gui

# Unit тесты
add_executable(TestGameEngine test_gameengine.cpp gameengine.cpp balloon.cpp)
target_link_libraries(TestGameEngine Qt6::Core Qt6::Test Qt6::Widgets Qt6::Gui)

add_executable(TestBalloon test_balloon.cpp balloon.cpp)
target_link_libraries(TestBalloon Qt6::Core Qt6::Test Qt6::Gui)
