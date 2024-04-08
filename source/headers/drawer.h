#pragma once
#include "global.h"

class Player;
class Maze;

class Drawer {
private:
    sf::Vector2u windowSize;
    std::string title;

public:
    sf::RenderWindow* window;

    Drawer(unsigned int width, unsigned int height, const std::string& title_ = "");
    ~Drawer();
    
    void toggleFullscreen();
    void eventHandler(Maze& maze, Player& player);
    void clearScreen(sf::Color color = sf::Color::White);
    void drawSegment(const sf::Vector2f& p1, const sf::Vector2f& p2, sf::Color color = sf::Color::Transparent);
    void drawRectangle(const sf::Vector2u& p1, const sf::Vector2u& p2, sf::Color color = sf::Color::Transparent);
    void drawCircle(const sf::Vector2f& center, unsigned int radius, sf::Color color = sf::Color::Transparent);
    void drawText(const std::string& text, unsigned int size, sf::Vector2f pos, sf::Color color = sf::Color::Black, sf::Text::Style style = sf::Text::Style::Regular);
};
