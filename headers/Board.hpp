#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <stdlib.h>
#include "Cell.hpp"
#include <queue>

#ifndef BOARD_HPP
#define BOARD_HPP

#define CELL_SIZE 32.0f
#define SCREEN_HEIGHT 672
#define SCREEN_WIDTH 640
#define ROWS 20
#define COLS 20
#define BOMB_C_EASY 135
#define BOMB_C_HARD 210

class Board {
public:

    Board();

    void drawSprite(sf::RenderWindow& window, sf::Sprite sprite,  float posX, float posY, int posRectX, int posRectY, int rectW, int rectH);

    void draw(sf::RenderWindow& window);

    void floodFill(int row, int col);

    void lostGameScreen(sf::RenderWindow& window, sf::Sprite numberSprite);

    void winGameScreen(sf::RenderWindow& window, sf::Sprite numberSprite);

    void revealCell(int row, int col);

    void putFlag(int row, int col);

    void restartButtonClick(float x, float y);

    void restartBoardR();

    void drawStatusBar(sf::RenderWindow& window);

    void drawMinesCount(sf::RenderWindow& window);

    void switchMode();

    bool gameOver;
    int rows;
    int cols;
    int mineCount;
    int revealedCount;
    int step;
    int foundMines; 
    bool easyMode;
    std::vector<std::vector<Cell>> cells;
    
private:

    void calculateNumbers();

    void firstMove(int r, int c);

    void firstMoveLogic(int r, int c);


    void generateBoard();
};
#endif // BOARD_HPP