#include <iostream>
#include "headers/drawer.h"
#include "headers/maze.h"
#include "headers/player.h"

using namespace std;

int main(int argc, char const *argv[]) {
    Drawer drawer(400, 400, "The Tu-Maze");

    Maze maze(20, 20);
    maze.generate(drawer);

    sf::Vector2i startPos = maze.getStartPos(drawer);
    Player player(startPos.x, startPos.y);

    /*  GAME LOOP */
    while (drawer.window->isOpen()) {
        drawer.eventHandler(maze, player);

        player.update(drawer, maze);

        sf::Vector2u windowSize = drawer.window->getSize();
        sf::Vector2u center{windowSize.x/2, windowSize.y/2};
        sf::Vector2i mousePos = sf::Mouse::getPosition(*drawer.window);

        // Draw & Display
        drawer.clearScreen(sf::Color::White);
        // TODO: 3D rendering
        drawer.drawRectangle({0, 0}, windowSize);
        maze.draw(drawer, sf::Color::Black);
        player.draw(drawer, sf::Color::Magenta);

        drawer.window->display();
    }

    return 0;
}
