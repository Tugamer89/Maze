#pragma once
#include <SFML/Graphics.hpp>

struct Point {
    int x;
    int y;
    Point(int x_, int y_) : x(x_), y(y_) {}
};

struct Size {
    unsigned int width;
    unsigned int height;
    Size(unsigned int width_, unsigned int height_) : width(width_), height(height_) {}
};

namespace drawer {
    sf::RenderWindow* initializeScreen(const Size& size, const std::string& title = "");
    void eventHandler(sf::RenderWindow*& window);
    void clearScreen(sf::RenderWindow*& window, sf::Color color = sf::Color::White);
    void drawSegment(sf::RenderWindow*& window, const Point& p1, const Point& p2);
    void drawRectangle(sf::RenderWindow*& window, const Point& p1, const Point& p2, sf::Color color = sf::Color(0, 0, 0, 0));
};
