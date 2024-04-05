#include <iostream>
#include "drawer.h"

using namespace std;

int main(int argc, char const *argv[]) {
    Size windowSize(800, 600);

    sf::RenderWindow* windowPtr = drawer::initializeScreen(windowSize, "Some cool tests");
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(windowSize.width/2 - shape.getRadius(), windowSize.height/2 - shape.getRadius());


    /*  GAME LOOP */
    while (windowPtr->isOpen()) {
        drawer::eventHandler(windowPtr);


        windowPtr->clear();
        windowPtr->draw(shape);
        windowPtr->display();
    }

    return 0;
}
