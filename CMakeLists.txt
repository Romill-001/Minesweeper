cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

# Установка пути к директории, где будут храниться исходники SFML
set(SFML_INSTALL_DIR ${CMAKE_BINARY_DIR}/SFML)


# Проверяем наличие SFML в директории CMake, если нет - загружаем
if(NOT EXISTS ${SFML_INSTALL_DIR})
    message("SFML not found, cloning from Git...")
    execute_process(COMMAND git clone --branch 2.5.1 --depth 1 https://github.com/SFML/SFML.git ${SFML_INSTALL_DIR})
endif()

# Указываем путь к заголовочным файлам SFML
include_directories(${SFML_INSTALL_DIR}/include)

# Добавляем подкаталоги с библиотеками SFML
add_subdirectory(${SFML_INSTALL_DIR})

# Создаем исполняемый файл из исходников
add_executable(exec src/main.cpp src/EventHandler.cpp src/Board.cpp src/Cell.cpp)

# Линкуем исполняемый файл с библиотеками SFML
target_link_libraries(exec sfml-graphics sfml-window sfml-system)
