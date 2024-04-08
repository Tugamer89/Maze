#include "headers/player.h"

using namespace std;

Player::Player(unsigned int x, unsigned int y, float speed_, float fov_) {
    coord.x = x;
    coord.y = y;
    fov = fov_ * M_PI / 180;
    speed = speed_;
    lookDir = 0;
}

void Player::moveBy(sf::Vector2f vec) {
    coord.x += vec.x;
    coord.y += vec.y;
}

void Player::calculateRays(Maze& maze) {
    rays.clear();

    for (float angle = lookDir - fov/2; angle <= lookDir + fov/2; angle += 1 * M_PI / 180) {
        Ray ray(coord, angle);

        ray.cast(maze.walls);

        if (ray.proiection != sf::Vector2f(-1, -1))
            rays.push_back(ray);
    }
}

void Player::drawVision(Drawer& drawer, sf::Color color) {
    for (Ray ray : rays)
        drawer.drawSegment(ray.center, ray.proiection, color);
}

void Player::draw(Drawer& drawer, sf::Color color) {
    drawer.drawCircle(coord, 2, color);

    float r = 6;
    sf::Vector2f p(coord.x + r*cos(lookDir), coord.y + r*sin(lookDir));
    drawer.drawSegment(coord, p, color);
}

void Player::update(Drawer& drawer, Maze& maze) {
    //cerr << lookDir * 180.f / M_PI << "\r";
    sf::Vector2i mousePos = sf::Mouse::getPosition(*drawer.window);
    lookDir = angleFromVec({mousePos.x - coord.x, mousePos.y - coord.y});

    sf::Vector2f movement(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed;

    if (movement.x != 0 && movement.y != 0) {
        float oblqSpeed = sqrt(pow(speed, 2) / 2);
        movement = {oblqSpeed * movement.x / abs(movement.x), oblqSpeed * movement.y / abs(movement.y)};
    }

    if (movement != sf::Vector2f(0, 0)) {
        movement.x *= drawer.window->getSize().x;
        movement.y *= drawer.window->getSize().y;
        
        Ray moveRay(coord, angleFromVec(movement));
        moveRay.cast(maze.walls);

        if (moveRay.proiection != sf::Vector2f(-1, -1) && distance(coord, moveRay.proiection) <= distance({0, 0}, movement))
            movement = sf::Vector2f(0, 0);

        moveBy(movement);
    }

    if (coord.x <= 0)
        coord.x = 1;
    if (coord.y <= 0)
        coord.y = 1;

    calculateRays(maze);
}

void Player::setFov(float newFov) {
    fov = newFov * M_PI / 180;
}
