#include "../headers/EventHandler.hpp"

sf::Vector2i getCellPosition(sf::Vector2i mousePosition)
{
    return (mousePosition) / static_cast<int>(CELL_SIZE);
}

void handleMouseButtonPressed(sf::RenderWindow &window, Board &board, sf::Event event) {
    sf::Vector2i mousePosition = {event.mouseButton.x, event.mouseButton.y};
    sf::Vector2i cellPosition = getCellPosition(mousePosition);
    if (event.mouseButton.button == sf::Mouse::Left) {
        if (!board.gameOver) {
            board.revealCell(cellPosition.y, cellPosition.x);
        } else {
            board.restartButtonClick(mousePosition.x, mousePosition.y);
        }
    }
    if (event.mouseButton.button == sf::Mouse::Right) {
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
            case sf::Keyboard::Enter:
                board.restartBoardEnter();
                break;
            }

        }
        
    }
}

void renderGame(sf::RenderWindow &window, Board &board) {
    board.draw(window);
}