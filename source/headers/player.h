#pragma once
#include "global.h"

class Ray;
class Maze;
class Drawer;

class Player {
private:
    float speed;    // in percentage of the total per frame
    float lookDir;  // in radians
    float fov;      // in radians
    std::vector<Ray> rays;

    void moveBy(sf::Vector2f vec);

public:
    sf::Vector2f coord;

    Player(unsigned int x, unsigned int y, float speed = 0.01, float fov = 60);
    void calculateRays(Maze& maze);
    void drawVision(Drawer& drawer, sf::Color color);
    void draw(Drawer& drawer,  sf::Color color);
    void update(Drawer& drawer, Maze& maze);
    void setFov(float newFov);
    void render3D(Drawer& drawer);
};
