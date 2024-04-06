#include "headers/player.h"

using namespace std;

Player::Player(unsigned int x, unsigned int y, float speed_) {
    coord.x = x;
    coord.y = y;
    speed = speed_;
    angle = 0;
}

void Player::moveBy(sf::Vector2f vec) {
    coord.x += vec.x;
    coord.y += vec.y;
}

void Player::draw(Drawer& drawer, sf::Color color) {
    drawer.drawCircle(coord, 2, color);

    float r = 6;
    sf::Vector2f p(coord.x + r*cos(angle), coord.y + r*sin(angle));
    drawer.drawSegment(coord, p, color);
}

void Player::update(Drawer& drawer, Maze& maze) {
    //cerr << angle * 180.f / M_PI << "\r";
    sf::Vector2i mousePos = sf::Mouse::getPosition(*drawer.window);
    angle = M_PI/2 - atan2(mousePos.x - coord.x, mousePos.y - coord.y);
    
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
