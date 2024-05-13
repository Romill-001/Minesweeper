#include "../headers/Board.hpp"
#include "../headers/Cell.hpp"

Board::Board() {
    gameOverWin = false;
    gameOverLose = false;
    easyMode = true;
    mineCount = BOMB_C_EASY;
    foundMines = 0;
    generateBoard();
}

void Board::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    
    sf::Sprite numberSprite;
    sf::Texture numberTexture;
    numberTexture.loadFromFile("res/Icons16.png");
    numberSprite.setTexture(numberTexture);

    sf::Sprite cellSprite;
    sf::Texture cellTexture;
    cellTexture.loadFromFile("res/cell.png");
    cellSprite.setTexture(cellTexture);

    sf::Sprite eCellSprite;
    sf::Texture eCellTexture;
    eCellTexture.loadFromFile("res/ecell.png");
    eCellSprite.setTexture(eCellTexture);

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (cells[i][j].type == CellType::Empty && cells[i][j].isRevealed) {
                drawSprite(window, eCellSprite, static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i + CELL_SIZE), 0, 0, CELL_SIZE, CELL_SIZE);
                if (0 < cells[i][j].minesAround) {
                    drawSprite(window, numberSprite, static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i + CELL_SIZE), CELL_SIZE * (cells[i][j].minesAround - 1), 0, CELL_SIZE, CELL_SIZE);
                }
            } else if (cells[i][j].type == CellType::Mine && cells[i][j].isRevealed) {
                drawSprite(window, numberSprite, static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i + CELL_SIZE), CELL_SIZE * 10, 0, CELL_SIZE, CELL_SIZE);
                gameOverLose = true;
            } else if (cells[i][j].isFagged) {
                isWin();
                drawSprite(window, numberSprite, static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i + CELL_SIZE), CELL_SIZE * 9, 0, CELL_SIZE, CELL_SIZE);
            } else {
                drawSprite(window, cellSprite, static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i + CELL_SIZE), 0, 0, CELL_SIZE, CELL_SIZE);
            }
        }
    }
    winGameScreen(window, numberSprite);
    lostGameScreen(window, numberSprite);
    drawStatusBar(window);
    drawMinesCount(window);
    window.display();
}

void Board::drawSprite(sf::RenderWindow& window, sf::Sprite sprite, float posX, float posY, int posRectX, int posRectY, int rectW, int rectH) {
    sprite.setPosition(posX, posY);
    sprite.setTextureRect(sf::IntRect(posRectX, posRectY, rectW, rectH));
    window.draw(sprite);
}

void Board::floodFill(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) return;
    if (cells[row][col].isRevealed || cells[row][col].type == CellType::Mine || (gameOverLose || gameOverWin)) return;

    cells[row][col].isRevealed = true;

    if (cells[row][col].type == CellType::Empty && cells[row][col].minesAround < 3) {
        floodFill(row - 1, col);
        floodFill(row + 1, col);
        floodFill(row, col - 1);
        floodFill(row, col + 1);
    } 
}

void Board::lostGameScreen(sf::RenderWindow& window, sf::Sprite numberSprite) {
    if (gameOverLose) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (cells[i][j].type == CellType::Mine) {
                    drawSprite(window, numberSprite, static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i + CELL_SIZE), CELL_SIZE * 10, 0, CELL_SIZE, CELL_SIZE);
                }
            }
        }
        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(128, 128, 128, 200));
        window.draw(overlay);
        sf::Sprite restartSprite;
        sf::Texture restartTexture;
        restartTexture.loadFromFile("res/restart_button.png");
        restartSprite.setTexture(restartTexture);
        drawSprite(window, restartSprite, CELL_SIZE * ROWS / 2 - 16, CELL_SIZE * COLS / 2 - 16, 0, 0, CELL_SIZE, CELL_SIZE);
        sf::Sprite lSprite;
        sf::Texture lTexture;
        lTexture.loadFromFile("res/lose_screen.png");
        lSprite.setTexture(lTexture);
        drawSprite(window, lSprite, CELL_SIZE * ROWS / 2 - 100, CELL_SIZE * COLS / 2 - 150, 0, 0, 200, CELL_SIZE * 2);
    }
}

void Board::isWin() {
    int tmp = 0;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (cells[i][j].type == CellType::Mine && cells[i][j].isFagged) {
                tmp++;
            }
        }
    }
    if (tmp == mineCount && tmp == foundMines)
        gameOverWin = true;
}
void Board::winGameScreen(sf::RenderWindow& window, sf::Sprite numberSprite) {
    if (gameOverWin) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (cells[i][j].type == CellType::Mine) {
                    drawSprite(window, numberSprite, static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i + CELL_SIZE), CELL_SIZE * 10, 0, CELL_SIZE, CELL_SIZE);
                }
            }
        }
        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(128, 128, 128, 200));
        window.draw(overlay);
        sf::Sprite restartSprite;
        sf::Texture restartTexture;
        restartTexture.loadFromFile("res/restart_button.png");
        restartSprite.setTexture(restartTexture);
        drawSprite(window, restartSprite, CELL_SIZE * ROWS / 2 - 16, CELL_SIZE * COLS / 2 - 16, 0, 0, CELL_SIZE, CELL_SIZE);
        sf::Sprite winSprite;
        sf::Texture winTexture;
        winTexture.loadFromFile("res/win_screen.png");
        winSprite.setTexture(winTexture);
        drawSprite(window, winSprite, CELL_SIZE * ROWS / 2 - 100, CELL_SIZE * COLS / 2 - 100, 0, 0, 200, CELL_SIZE * 2);
    }
}

void Board::revealCell(int row, int col) {
    if (step == 0) {
        firstMove(row, col);
        calculateNumbers();
    }
    if (cells[row][col].type == CellType::Mine) {
        cells[row][col].isRevealed = true;
    }
    floodFill(row, col);
    step = 1;
}

void Board::putFlag(int row, int col) {
    if (step == 1 && (!gameOverLose && !gameOverWin)) {
        if (!cells[row][col].isRevealed) {
            cells[row][col].isFagged = true;
            foundMines++;
        }
    } else {
        return;
    }
}

void Board::restartBoardR() {
    if (!gameOverLose || !gameOverWin) {
        gameOverLose = false;
        gameOverWin = false;
        foundMines = 0;
        cells.clear();
        step = 0;
        generateBoard();
    }
}

void Board::calculateNumbers() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (cells[i][j].type == CellType::Empty) {
                int minesCount = 0;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS && cells[ni][nj].type == CellType::Mine) {
                            minesCount++;
                        }
                    }
                }
                cells[i][j].minesAround = minesCount;
            }
        }
    }
}

void Board::firstMove(int row, int col) {
    firstMoveLogic(row, col);
    firstMoveLogic(row - 1, col);
    firstMoveLogic(row + 1, col);
    firstMoveLogic(row, col - 1);
    firstMoveLogic(row, col + 1);
    firstMoveLogic(row + 1, col + 1);
    firstMoveLogic(row + 1 , col - 1);
    firstMoveLogic(row - 1, col - 1);
    firstMoveLogic(row - 1, col + 1);
}

void Board::firstMoveLogic(int x, int y) {
    if (cells[x][y].type == CellType::Mine) {
        cells[x][y].type = CellType::Empty;
        int xRand = rand() % ROWS;
        int yRand = rand() % COLS;
        if (cells[xRand][yRand].type != CellType::Mine && (xRand != x && yRand != y)) {
            cells[xRand][yRand].type = CellType::Mine;
        }
    }
}

void Board::generateBoard() {
    cells.assign(ROWS, std::vector<Cell>(COLS, Cell()));
    int placedMines = 0;
    while (placedMines < mineCount) {
        int xRand = rand() % ROWS;
        int yRand = rand() % COLS;
        if (cells[xRand][yRand].type != CellType::Mine) {
            cells[xRand][yRand].type = CellType::Mine;
            placedMines++;
        }
    }

    std::mt19937 rng{std::random_device{}()};
    std::shuffle(cells.begin(), cells.end(), rng);

}

void Board::restartButtonClick(float x, float y) {\
    if (x > static_cast<float>(CELL_SIZE * ROWS / 2 - 16) && x < static_cast<float>(CELL_SIZE * COLS / 2 + 16) &&
    y > static_cast<float>(CELL_SIZE * COLS / 2 - 16) && y < static_cast<float>(CELL_SIZE * COLS / 2 + 16)){
        step = 0;
        gameOverLose = false;
        gameOverWin = false;
        foundMines = 0;
        generateBoard();
    }
}

void Board::drawStatusBar(sf::RenderWindow& window) {
    sf::Sprite statusSprite;
    sf::Texture statusTexture;
    std::string str = (easyMode ? "easy" : "hard");
    statusTexture.loadFromFile("res/status_bar_" + str + ".png");
    statusSprite.setTexture(statusTexture);
    drawSprite(window, statusSprite, 0, 0, 0, 0, SCREEN_WIDTH, CELL_SIZE);
}

void Board::drawMinesCount(sf::RenderWindow& window) {
    sf::Sprite mSpriteA;
    sf::Sprite mSpriteB;
    sf::Sprite mSpriteC;
    sf::Texture Texture;
    Texture.loadFromFile("res/numbers_for_mines.png");
    mSpriteA.setTexture(Texture);
    mSpriteB.setTexture(Texture);
    mSpriteC.setTexture(Texture);
    drawSprite(window, mSpriteA, 470, 0, CELL_SIZE * (((mineCount - foundMines)/100 - 1) == -1 ? 9 : (mineCount - foundMines)/100 - 1), 0, CELL_SIZE, CELL_SIZE);
    drawSprite(window, mSpriteB, 470 + CELL_SIZE, 0, CELL_SIZE * (((mineCount - foundMines)/10%10 - 1) == -1 ? 9 : (mineCount - foundMines)/10%10 - 1), 0, CELL_SIZE, CELL_SIZE);
    drawSprite(window, mSpriteC, 470 + 2 * CELL_SIZE, 0, CELL_SIZE * (((mineCount - foundMines)%10 - 1) == -1 ? 9 : (mineCount - foundMines)%10 - 1), 0, CELL_SIZE, CELL_SIZE);

}

void Board::switchMode() {
    easyMode = !easyMode;
    if (easyMode) {
        mineCount = BOMB_C_EASY;
    } else {
        mineCount = BOMB_C_HARD;
    }
    restartBoardR();
}