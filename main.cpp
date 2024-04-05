#include <iostream>
#include "drawer.h"

using namespace std;

int main(int argc, char const *argv[]) {
    string title = "Some cool tests";
    sf::RenderWindow* windowPtr = drawer::initializeScreen(800, 600, title);
    
    /*  GAME LOOP */
    while (windowPtr->isOpen()) {
        drawer::eventHandler(windowPtr);

        sf::Vector2u windowSize = windowPtr->getSize();
        sf::Vector2u center{windowSize.x/2, windowSize.y/2};
        sf::Vector2i mousePos = sf::Mouse::getPosition(*windowPtr);

        // Draw everything
        drawer::clearScreen(windowPtr, sf::Color::White);
        drawer::drawRectangle(windowPtr, {center.x - windowSize.x*.02, center.y - windowSize.y*.02}, {center.x + windowSize.x*.02, center.y + windowSize.y*.02}, sf::Color::Magenta);
        drawer::drawSegment(windowPtr, {0, mousePos.y}, {windowSize.x, mousePos.y}, sf::Color::Black);
        drawer::drawSegment(windowPtr, {mousePos.x, 0}, {mousePos.x, windowSize.y}, sf::Color::Black);

        windowPtr->display();
    }

    return 0;
}
