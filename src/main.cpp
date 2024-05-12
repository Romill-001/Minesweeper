#include <SFML/Graphics.hpp>
#include "../headers/Board.hpp"
#include "../headers/EventHandler.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    Board board;
    while (window.isOpen())
    {
        handleEvent(window, board);
        renderGame(window, board);
    }

    return 0;
}