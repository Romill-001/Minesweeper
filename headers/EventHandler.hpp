#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"

#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

sf::Vector2i getCellPosition(sf::Vector2i mousePosition);

void handleMouseButtonPressed(sf::RenderWindow &window, Board &board, sf::Event event);

void handleEvent(sf::RenderWindow &window, Board &board);

void renderGame(sf::RenderWindow &window, Board &board);

#endif //EVENT_HANDLER_HPP