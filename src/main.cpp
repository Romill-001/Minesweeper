#include <SFML/Graphics.hpp>
#include "../headers/Board.hpp"
#include "../headers/EventHandler.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(32 * ROW, 32 * COL), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    Board board(ROW, COL, BOMBS_C);

    while (window.isOpen())
    {
        handleEvent(window, board);
        renderGame(window, board);
    }

    return 0;
}