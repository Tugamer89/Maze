#pragma once
#include "global.h"

class Ray {
private:
    float angle;

    sf::Vector2f cast(sf::VertexArray wall);
    
public:
    sf::Vector2f center;
    sf::Vector2f proiection;

    Ray(sf::Vector2f center, float angle);
    void cast(std::vector<sf::VertexArray> walls);
};
