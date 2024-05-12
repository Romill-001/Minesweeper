#include "../headers/EventHandler.hpp"

sf::Vector2i getCellPosition(sf::Vector2i mousePosition) {
   sf::Vector2i tmp = mousePosition;
   tmp.x /= CELL_SIZE;
   tmp.y = (tmp.y - CELL_SIZE) / CELL_SIZE;
   return tmp;
}

void handleMouseButtonPressed(sf::RenderWindow &window, Board &board, sf::Event event) {
    sf::Vector2i mousePosition = {event.mouseButton.x, event.mouseButton.y};
    sf::Vector2i cellPosition = getCellPosition(mousePosition);
    if (event.mouseButton.button == sf::Mouse::Left) {
        if (!board.gameOver && (mousePosition.y > CELL_SIZE - 1)) {
            board.revealCell(cellPosition.y, cellPosition.x);
        } else {
            board.restartButtonClick(mousePosition.x, mousePosition.y);
        }
    }
    if (event.mouseButton.button == sf::Mouse::Right && (mousePosition.y > CELL_SIZE - 1)) {
        board.putFlag(cellPosition.y, cellPosition.x);
    }
}

void handleEvent(sf::RenderWindow &window, Board &board) {
    sf::Event event;
    while(window.pollEvent(event)){
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
            handleMouseButtonPressed(window, board, event);
            break;
        case sf::Event::Closed:
            window.close();
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::R:
                board.restartBoardR();
                break;
            }
            case sf::Keyboard::Q:
            board.easyMode = !board.easyMode;
            if (board.easyMode) {
                board.mineCount = 135;
            } else {
                board.mineCount = 210;
            }
            board.restartBoardR();
            break;
        }
        
    }
}

void renderGame(sf::RenderWindow &window, Board &board) {
    board.draw(window);
}