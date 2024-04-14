#pragma once
#include "global.h"

class Ray;
class Maze;
class Drawer;

class Player {
private:
    float speed;    // in percentage of total pixels per second
    float lookSens; // in degrees per second
    float lookDir;  // in radians
    float fov;      // in radians
    std::vector<Ray> rays;

    void moveBy(sf::Vector2f vec);

public:
    sf::Vector2f coord;

    Player(unsigned int x, unsigned int y, float speed = 0.1, float lookSens = 180, float fov = 100);
    void calculateRays(Maze& maze);
    void drawVision(Drawer& drawer, sf::Color color);
    void draw(Drawer& drawer,  sf::Color color);
    void update(Drawer& drawer, Maze& maze, float delta);
    void setFov(float newFov);
    void render3D(Drawer& drawer);
};
