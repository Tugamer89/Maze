#include "drawer.h"

using namespace std;

sf::RenderWindow* drawer::initializeScreen(unsigned int width, unsigned int height, const std::string& title) {
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    return window;
}

void drawer::eventHandler(sf::RenderWindow*& window, const std::string& title) {
    sf::Event event;
        
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::F11)
                toggleFullscreen(window, title);
            break;

        case sf::Event::Resized:
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
            }
            break;
        
        default:
            break;
        }
    }
}

void drawer::toggleFullscreen(sf::RenderWindow*& window, const std::string& title) {
    bool isFullscreen = window->isOpen() && window->getSize() == sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    window->close();
    if (!isFullscreen)
        window->create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
    else
        window->create(sf::VideoMode(800, 600), title, sf::Style::Default);
}

void drawer::clearScreen(sf::RenderWindow*& window, sf::Color color) {
    window->clear(color);
}

void drawer::drawSegment(sf::RenderWindow*& window, const sf::Vector2u& p1, const sf::Vector2u& p2, sf::Color color) {
    sf::VertexArray line(sf::Lines, 2);

    line[0].position = sf::Vector2f(p1.x, p1.y);
    line[0].color = color;
    line[1].position = sf::Vector2f(p2.x, p2.y);
    line[1].color = color;

    window->draw(line);
}

void drawer::drawRectangle(sf::RenderWindow*& window, const sf::Vector2u& p1, const sf::Vector2u& p2, sf::Color color) {
    double width = abs((int)p1.x - (int)p2.x);
    double height = abs((int)p1.y - (int)p2.y);

    double left = min(p1.x, p2.x);
    double top = min(p1.y, p2.y);

    sf::RectangleShape rectangle(sf::Vector2f(width, height));

    rectangle.setPosition(left, top);
    rectangle.setFillColor(color);

    window->draw(rectangle);
}
