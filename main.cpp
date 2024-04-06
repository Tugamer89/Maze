#include <iostream>
#include "drawer.h"
#include "maze.h"

using namespace std;

int main(int argc, char const *argv[]) {
    Drawer drawer(400, 400, "Maze generator");
    Maze maze(20, 20);
    
    cerr << endl;

    maze.generate();
    cerr << "DEBUG > Maze generated!" << endl;

    /*  GAME LOOP */
    while (drawer.window->isOpen()) {
        drawer.eventHandler();

        sf::Vector2u windowSize = drawer.window->getSize();
        sf::Vector2u center{windowSize.x/2, windowSize.y/2};
        sf::Vector2i mousePos = sf::Mouse::getPosition(*drawer.window);

        // Draw & Display
        drawer.clearScreen(sf::Color::White);
        maze.draw(drawer, sf::Color::Black, sf::Color::Transparent);
        
        drawer.window->display();
    }

    return 0;
}
