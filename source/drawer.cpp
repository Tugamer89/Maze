#include "headers/drawer.h"

using namespace std;

Drawer::Drawer(unsigned int width, unsigned int height, const std::string& title_) {
    windowSize = {width, height};
    title = title_;
    window = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

Drawer::~Drawer() {
    delete window;
}

void Drawer::eventHandler(Maze& maze, Player& player) {
    sf::Event event;

    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::F11 || event.key.code == sf::Keyboard::Escape)
                toggleFullscreen();
            break;

        case sf::Event::Resized:
            {
                sf::Vector2i newSize(event.size.width, event.size.height);
                sf::Vector2i sizeDiff(windowSize.x - newSize.x, windowSize.y - newSize.y);

                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));

                player.coord.x *= (float)newSize.x / windowSize.x;
                player.coord.y *= (float)newSize.y / windowSize.y;

                windowSize = {newSize.x, newSize.y};

                maze.calculateWalls(*this);
            }
            break;
        
        default:
            break;
        }
    }
}

void Drawer::toggleFullscreen() {
    bool isFullscreen = window->isOpen() && window->getSize() == sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    window->close();
    if (!isFullscreen)
        window->create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
    else
        window->create(sf::VideoMode(windowSize.x, windowSize.y), title, sf::Style::Default);
}

void Drawer::clearScreen(sf::Color color) {
    window->clear(color);
}

void Drawer::drawSegment(const sf::Vector2f& p1, const sf::Vector2f& p2, sf::Color color) {
    sf::VertexArray line(sf::Lines, 2);

    line[0].position = p1;
    line[0].color = color;
    line[1].position = p2;
    line[1].color = color;

    window->draw(line);
}

void Drawer::drawRectangle(const sf::Vector2u& p1, const sf::Vector2u& p2, sf::Color color) {
    double width = abs((int)p1.x - (int)p2.x);
    double height = abs((int)p1.y - (int)p2.y);

    double left = min(p1.x, p2.x);
    double top = min(p1.y, p2.y);

    sf::RectangleShape rectangle(sf::Vector2f(width, height));

    rectangle.setPosition(left, top);
    rectangle.setFillColor(color);

    window->draw(rectangle);
}

void Drawer::drawCircle(const sf::Vector2f& center, unsigned int radius, sf::Color color) {
    sf::CircleShape circle(radius);

    circle.setPosition(center.x - radius, center.y - radius);
    circle.setFillColor(color);

    window->draw(circle);
}
