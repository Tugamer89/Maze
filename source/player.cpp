#include "headers/player.h"

using namespace std;

Player::Player(unsigned int x, unsigned int y, float speed_, float fov_) {
    coord.x = x;
    coord.y = y;
    fov = fov_ * M_PI / 360;
    speed = speed_;
    lookDir = 0;
}

void Player::moveBy(sf::Vector2f vec) {
    coord.x += vec.x;
    coord.y += vec.y;
}

void Player::drawVision(Drawer& drawer, Maze& maze, sf::Color color) {
    for (float angle = lookDir - fov/2; angle <= lookDir + fov/2; angle += 1 * M_PI / 360) {
        float ang = angle;
        Ray ray(coord, ang);

        struct {
            sf::Vector2f point = {-1, -1};
            float dist = MAXFLOAT;
        } closest;

        for (sf::VertexArray wall : maze.walls) {
            sf::Vector2f p = ray.cast(wall);
            float distance = sqrt(pow(p.x - coord.x, 2) + pow(p.y - coord.y, 2));

            if (p != sf::Vector2f(-1, -1) && distance < closest.dist) {
                closest.point = p;
                closest.dist = distance;
            }
        }

        if (closest.point != sf::Vector2f(-1, -1))
            drawer.drawSegment(coord, closest.point, color);
    }
}

void Player::draw(Drawer& drawer, sf::Color color) {
    drawer.drawCircle(coord, 2, color);

    float r = 6;
    sf::Vector2f p(coord.x + r*cos(lookDir), coord.y + r*sin(lookDir));
    drawer.drawSegment(coord, p, color);
}

void Player::update(Drawer& drawer, Maze& maze) {
    cerr << lookDir * 180.f / M_PI << "\r";
    sf::Vector2i mousePos = sf::Mouse::getPosition(*drawer.window);
    lookDir = -atan2(mousePos.x - coord.x, mousePos.y - coord.y) + M_PI/2;


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

    movement.x *= drawer.window->getSize().x;
    movement.y *= drawer.window->getSize().y;

    moveBy(movement);
}
