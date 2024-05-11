#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <stdlib.h>
#include "Cell.hpp"
#include <queue>

#ifndef BOARD_HPP
#define BOARD_HPP

#define ROW 10
#define COL 10
#define BOMBS_C 34
#define CELL_SIZE 32.0f


class Board {
public:
    bool gameOver;

    Board(int rows, int cols, int mineCount);

    void draw(sf::RenderWindow& window);

    void floodFill(int row, int col);

    void lostGameScreen(sf::RenderWindow& window, sf::Sprite numberSprite);

    void revealCell(int row, int col);

    void putFlag(int row, int col);

    void restartButtonClick(float x, float y);

    void restartBoardEnter();

private:
    int rows;
    int cols;
    int mineCount;
    int revealedCount;
    int step;
    int foundMines;


    std::vector<std::vector<Cell>> cells;

    void calculateNumbers();

    void firstMove(int r, int c);

    void generateBoard();
};
#endif // BOARD_HPP