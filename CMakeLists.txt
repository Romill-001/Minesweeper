cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(app src/main.cpp)

target_link_libraries(app sfml-graphics sfml-window sfml-system)