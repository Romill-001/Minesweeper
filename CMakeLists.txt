cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

set (CMAKE_CXX_STANDARD 11)

set(SFML_INSTALL_DIR ${CMAKE_BINARY_DIR}/SFML)

if(NOT EXISTS ${SFML_INSTALL_DIR})
    message("SFML not found, cloning from Git...")
    execute_process(COMMAND git clone --branch 2.5.1 --depth 1 https://github.com/SFML/SFML.git ${SFML_INSTALL_DIR})
endif()

include_directories(${SFML_INSTALL_DIR}/include)

add_subdirectory(${SFML_INSTALL_DIR})

add_executable(Minesweeper src/main.cpp src/EventHandler.cpp src/Board.cpp src/Cell.cpp)

target_link_libraries(
    Minesweeper 
    sfml-graphics 
    sfml-window 
    sfml-system
)

set(GTEST_INSTALL_DIR ${CMAKE_BINARY_DIR}/googletest)
if(NOT EXISTS ${GTEST_INSTALL_DIR})
    message("Google Test not found, cloning from Git...")
    execute_process(COMMAND git clone --branch release-1.11.0 --depth 1 https://github.com/google/googletest.git ${GTEST_INSTALL_DIR})
endif()

include_directories(${GTEST_INSTALL_DIR}/googletest/include)

add_subdirectory(${GTEST_INSTALL_DIR})

add_executable(test tests/main.cpp tests/test_cases.cpp src/Board.cpp src/EventHandler.cpp src/Cell.cpp)

target_link_libraries(
    test 
    sfml-graphics 
    sfml-window 
    sfml-system 
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
    GTest::gmock_main
)

add_dependencies(test gtest)

add_custom_command(TARGET test POST_BUILD COMMAND test)
