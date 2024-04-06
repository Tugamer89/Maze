#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Drawer {
private:
    sf::Vector2u windowSize;
    std::string title;

public:
    sf::RenderWindow* window;

    Drawer(unsigned int width, unsigned int height, const std::string& title_ = "");
    ~Drawer();
    
    void toggleFullscreen();
    void eventHandler();
    void clearScreen(sf::Color color = sf::Color::White);
    void drawSegment(const sf::Vector2u& p1, const sf::Vector2u& p2, sf::Color color = sf::Color(0, 0, 0, 0));
    void drawRectangle(const sf::Vector2u& p1, const sf::Vector2u& p2, sf::Color color = sf::Color(0, 0, 0, 0));
};
