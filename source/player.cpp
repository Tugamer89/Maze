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

    // TODO: increase angle not constantly
    const float numRays = 100;
    const float angleIncrement = fov/numRays;
    for (float angle = lookDir - fov/2; angle <= lookDir + fov/2;) {
        Ray ray(coord, angle);

        ray.cast(maze.walls);

        if (ray.proiection != sf::Vector2f(-1, -1))
            rays.push_back(ray);

        angle += angleIncrement;
    }
}

void Player::drawVision(Drawer& drawer, sf::Color color) {
    for (Ray ray : rays)
        drawer.drawSegment(ray.center, ray.proiection, color);
}

void Player::draw(Drawer& drawer, sf::Color color) {
    drawer.drawCircle(coord, 2, color);

    float r = 10;
    sf::Vector2f p(coord.x + r*cos(lookDir), coord.y + r*sin(lookDir));
    drawer.drawSegment(coord, p, color);
}

void Player::update(Drawer& drawer, Maze& maze) {
    float sens = 5 * M_PI / 180.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        lookDir -= sens;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        lookDir += sens;

    if (lookDir < 0)
        lookDir += 2 * M_PI;
    else if (lookDir > 2 * M_PI)
        lookDir -= 2 * M_PI;

    sf::Vector2f forwardMovement(cos(lookDir) * speed, sin(lookDir) * speed);
    sf::Vector2f lateralMovement(-sin(lookDir) * speed, cos(lookDir) * speed);

    sf::Vector2f movement(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement += forwardMovement;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement -= lateralMovement;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement -= forwardMovement;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement += lateralMovement;

    movement.x *= drawer.getMiniMapSize().x;
    movement.y *= drawer.getMiniMapSize().y;
        
    if (movement != sf::Vector2f(0, 0)) {
        Ray moveRay(coord, angleFromVec(movement));
        moveRay.cast(maze.walls);

        if (moveRay.proiection != sf::Vector2f(-1, -1) && distance(coord, moveRay.proiection) <= distance({0, 0}, movement))
            movement = sf::Vector2f(0, 0);

        moveBy(movement);
    }

    calculateRays(maze);
}

void Player::setFov(float newFov) {
    fov = newFov * M_PI / 180;
}

void Player::render3D(Drawer& drawer) {
    int width = drawer.window->getSize().x;
    int height = drawer.window->getSize().y;

    for (size_t i = 0; i < rays.size(); ++i) {
        Ray ray = rays[i];

        float dist =  distance(ray.center, ray.proiection);
        
        float angleDifference = lookDir - ray.angle;
        float correctedDistance = dist * cos(angleDifference);

        float maxBrightness = 255;
        float minBrightness = 50;
        float brightness = log(correctedDistance) / log(1.03) / (maxBrightness - minBrightness) * maxBrightness + minBrightness;
        brightness = maxBrightness - brightness;
        brightness = max(minBrightness, brightness);
        brightness = min(maxBrightness, brightness);

        float maxRayHeight = height;
        float minRayHeight = 80;
        float rayHeight = minRayHeight + (maxRayHeight - minRayHeight) / correctedDistance;
        rayHeight = min(maxRayHeight, rayHeight);

        sf::Vector2u top_left(i * width / rays.size(), height / 2 - rayHeight / 2);
        sf::Vector2u bottom_right((i + 1) * width / rays.size(), height / 2 + rayHeight / 2);

        drawer.drawRectangle(top_left, bottom_right, sf::Color(brightness, brightness, brightness));
    }
}
