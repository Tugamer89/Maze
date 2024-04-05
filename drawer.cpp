#include "drawer.h"

using namespace std;

sf::RenderWindow* drawer::initializeScreen(const Size& size, const std::string& title) {
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(size.width, size.height), title);
    return window;
}

void drawer::eventHandler(sf::RenderWindow*& window) {
    sf::Event event;
        
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;

        
        case sf::Event::Resized:
            window->setSize(sf::Vector2u(event.size.width, event.size.height));
            break;
        
        default:
            break;
        }
    }
}

void drawer::clearScreen(sf::RenderWindow*& window, sf::Color color) {

}

void drawer::drawSegment(sf::RenderWindow*& window, const Point& p1, const Point& p2) {

}

void drawRectangle(sf::RenderWindow*& window, const Point& p1, const Point& p2, sf::Color color) {

}
