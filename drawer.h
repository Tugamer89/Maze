#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace drawer {
    sf::RenderWindow* initializeScreen(unsigned int width, unsigned int height, const std::string& title = "");
    void toggleFullscreen(sf::RenderWindow*& window, const std::string& title = "");
    void eventHandler(sf::RenderWindow*& window, const std::string& title = "");
    void clearScreen(sf::RenderWindow*& window, sf::Color color = sf::Color::White);
    void drawSegment(sf::RenderWindow*& window, const sf::Vector2u& p1, const sf::Vector2u& p2, sf::Color color = sf::Color(0, 0, 0, 0));
    void drawRectangle(sf::RenderWindow*& window, const sf::Vector2u& p1, const sf::Vector2u& p2, sf::Color color = sf::Color(0, 0, 0, 0));
};
