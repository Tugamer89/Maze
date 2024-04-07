#include "headers/ray.h"

using namespace std;

Ray::Ray(sf::Vector2f center_, float angle_) {
    proiection = {-1, -1};
    center = center_;
    angle = angle_;
}

/* https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line_segment */
sf::Vector2f Ray::cast(sf::VertexArray wall) {
    float x1 = wall[0].position.x;
    float y1 = wall[0].position.y;
    float x2 = wall[1].position.x;
    float y2 = wall[1].position.y;

    float x3 = center.x;
    float y3 = center.y;
    float x4 = center.x + 10*cos(angle);
    float y4 = center.y + 10*sin(angle);

    const float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0)
        return {-1, -1};

    const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    if (u < 0 || t < 0 || t > 1)
        return {-1, -1};

    sf::Vector2f point;
    point.x = x1 + t * (x2 - x1);
    point.y = y1 + t * (y2 - y1);
    return point;
}

void Ray::cast(vector<sf::VertexArray> walls) {
    float closestDist = MAXFLOAT;

    for (sf::VertexArray wall : walls) {
        sf::Vector2f p = cast(wall);
        float dist = distance(p, center);

        if (p != sf::Vector2f(-1, -1) && dist < closestDist) {
            proiection = p;
            closestDist = dist;
        }
    }
}
