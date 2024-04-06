#pragma once
#include "global.h"

class Maze;
class Drawer;

class Player {
private:
    float speed;    // in percentage of the total
    float angle;    // in radians

    void moveBy(sf::Vector2f vec);

public:
    sf::Vector2f coord;

    Player(unsigned int x, unsigned int y, float speed = 0.001);
    void draw(Drawer& drawer, sf::Color color);
    void update(Drawer& drawer, Maze& maze);
};
