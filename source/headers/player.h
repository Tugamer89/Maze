#pragma once
#include "global.h"

class Maze;
class Drawer;

class Player {
private:
    float speed;    // in percentage of the total per frame
    float lookDir;  // in radians
    float fov;      // in radians

    void moveBy(sf::Vector2f vec);

public:
    sf::Vector2f coord;

    Player(unsigned int x, unsigned int y, float speed = 0.01, float fov = 60);
    void drawVision(Drawer& drawer, Maze& maze, sf::Color color);
    void draw(Drawer& drawer,  sf::Color color);
    void update(Drawer& drawer, Maze& maze);
};
