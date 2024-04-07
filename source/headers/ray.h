#pragma once
#include "global.h"

class Ray {
private:
    sf::Vector2f center;
    float angle;

public:
    Ray(sf::Vector2f center, float angle);
    sf::Vector2f cast(sf::VertexArray wall);
};
