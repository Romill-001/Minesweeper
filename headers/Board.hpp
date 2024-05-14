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

    void isWin();
    
    void gameOverScreen(sf::RenderWindow& window, sf::Sprite numberSprite, bool gameState, std::string path);

    void revealCell(int row, int col);

    void putFlag(int row, int col);

    void restartButtonClick(float x, float y);

    void restartBoardR();

    void drawStatusBar(sf::RenderWindow& window);

    void drawMinesCount(sf::RenderWindow& window);

    void switchMode();

    bool getGameOverWin();

    void setGameOverWin(const bool gameState);

    bool getGameOverLose();

    void setGameOverLose(const bool gameState);
    
    int getMineCount();

    void setMineCount(const int newCount);

    int getStep();

    void setStep(const int newStep);

    int getFoundMines();

    void setFoundMines(const int newCount);

    bool getMode();

    void setMode(const bool modeState);

    std::vector<std::vector<Cell>> getCells();

    void setCells(const std::vector<std::vector<Cell>> newCells);
private:
    bool gameOverWin;

    bool gameOverLose;

    int mineCount;

    int step;

    int foundMines; 

    bool easyMode;

    std::vector<std::vector<Cell>> cells;

    void calculateNumbers();

    void firstMove(int r, int c);

    void firstMoveLogic(int r, int c);

    void generateBoard();
};
#endif // BOARD_HPP