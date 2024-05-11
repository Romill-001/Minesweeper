#include "../headers/Board.hpp"
#include "../headers/Cell.hpp"

Board::Board(int rows, int cols, int mineCount) 
    : rows(rows), cols(cols), mineCount(mineCount), revealedCount(0), gameOver(false), step(0) {
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

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (cells[i][j].type == CellType::Empty && cells[i][j].isRevealed) {
                eCellSprite.setPosition(static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i));
                eCellSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                window.draw(eCellSprite);
                if (0 < cells[i][j].minesAround) {
                    numberSprite.setPosition(static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i));
                    numberSprite.setTextureRect(sf::IntRect(CELL_SIZE * (cells[i][j].minesAround - 1), 0, CELL_SIZE, CELL_SIZE));
                    window.draw(numberSprite);
                }
            } else if (cells[i][j].type == CellType::Mine && cells[i][j].isRevealed) {
                numberSprite.setPosition(static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i));
                numberSprite.setTextureRect(sf::IntRect(CELL_SIZE * 10, 0, CELL_SIZE, CELL_SIZE));
                window.draw(numberSprite);
                gameOver = true;
            } else if (cells[i][j].type == CellType::Flag) {
                numberSprite.setPosition(static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i));
                numberSprite.setTextureRect(sf::IntRect(CELL_SIZE * 9, 0, CELL_SIZE, CELL_SIZE));
                window.draw(numberSprite);
            } else {
                cellSprite.setPosition(static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i));
                cellSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                window.draw(cellSprite);
            }
        }
    }
    if(gameOver) {
        lostGameScreen(window, numberSprite);
    }
    window.display();
}

void Board::floodFill(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) return;
    if (cells[row][col].isRevealed || cells[row][col].type == CellType::Mine || gameOver) return;

    cells[row][col].isRevealed = true;
    revealedCount++;

    if (cells[row][col].type == CellType::Empty && cells[row][col].minesAround < 3) {
        floodFill(row - 1, col);
        floodFill(row + 1, col);
        floodFill(row, col - 1);
        floodFill(row, col + 1);
    } 

}

void Board::lostGameScreen(sf::RenderWindow& window, sf::Sprite numberSprite) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (cells[i][j].type == CellType::Mine || cells[i][j].type == CellType::Flag) {
                numberSprite.setPosition(static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i));
                numberSprite.setTextureRect(sf::IntRect(CELL_SIZE * 10, 0, CELL_SIZE, CELL_SIZE));
                window.draw(numberSprite);
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
    restartSprite.setPosition(CELL_SIZE * ROW / 2 - 16, CELL_SIZE * COL / 2 - 16);
    restartSprite.setTextureRect(sf::IntRect(0,0, CELL_SIZE, CELL_SIZE));
    window.draw(restartSprite);

}

void Board::revealCell(int row, int col) {
    if (step == 0) {
        firstMove(row, col);
        firstMove(row - 1, col);
        firstMove(row + 1, col);
        firstMove(row, col - 1);
        firstMove(row, col + 1);
        firstMove(row + 1, col + 1);
        firstMove(row + 1 , col - 1);
        firstMove(row - 1, col - 1);
        firstMove(row - 1, col + 1);
        calculateNumbers();
    }
    if (cells[row][col].type == CellType::Mine) {
        cells[row][col].isRevealed = true;
    }
    floodFill(row, col);
    step = 1;
}

void Board::putFlag(int row, int col) {
    if (!cells[row][col].isRevealed)
        cells[row][col].type = CellType::Flag;
    foundMines++;
}

void Board::restartBoardEnter() {
    if (!gameOver) {
        step = 0;
        generateBoard();
    }
}

void Board::calculateNumbers() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (cells[i][j].type == CellType::Empty) {
                int mineCount = 0;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && cells[ni][nj].type == CellType::Mine) {
                            mineCount++;
                        }
                    }
                }
                cells[i][j].minesAround = mineCount;
            }
        }
    }
}
void Board::firstMove(int r, int c) {
    if (cells[r][c].type == CellType::Mine) {
        cells[r][c].type = CellType::Empty;
        int row = rand() % rows;
        int col = rand() % cols;
        if (cells[row][col].type != CellType::Mine && (row != r && col != c)) {
            cells[row][col].type = CellType::Mine;
        }
    }
}

void Board::generateBoard() {
    cells.assign(rows, std::vector<Cell>(cols, Cell()));
    int placedMines = 0;
    while (placedMines < mineCount) {
        int row = rand() % rows;
        int col = rand() % cols;
        if (cells[row][col].type != CellType::Mine) {
            cells[row][col].type = CellType::Mine;
            placedMines++;
        }
    }

    std::mt19937 rng{std::random_device{}()};
    std::shuffle(cells.begin(), cells.end(), rng);

}
//restartSprite.setPosition(CELL_SIZE * ROW / 2 - 16, CELL_SIZE * COL / 2 - 16);

void Board::restartButtonClick(float x, float y) {\
    if (x > static_cast<float>(CELL_SIZE * ROW / 2 - 16) && x < static_cast<float>(CELL_SIZE * ROW / 2 + 16) &&
    y > static_cast<float>(CELL_SIZE * COL / 2 - 16) && y < static_cast<float>(CELL_SIZE * COL / 2 + 16)){
        step = 0;
        gameOver = false;
        generateBoard();
    }
}