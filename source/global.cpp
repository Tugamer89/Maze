#include "headers/global.h"

using namespace std;

float distance(sf::Vector2f p1, sf::Vector2f p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

float angleFromVec(sf::Vector2f vec) {
    return M_PI/2 - atan2(vec.x, vec.y);
}
