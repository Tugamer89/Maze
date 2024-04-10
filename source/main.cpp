#include <iostream>
#include <chrono>
#include "headers/drawer.h"
#include "headers/player.h"
#include "headers/maze.h"
#include "headers/ray.h"

using namespace std;

int main(int argc, char const *argv[]) {
    Drawer drawer(600, 600, "The Tu-Maze");

    Maze maze(5, 5);
    maze.generate(drawer);

    sf::Vector2i startPos = maze.getStartPos(drawer);
    Player player(startPos.x, startPos.y);

    auto startTime = chrono::high_resolution_clock::now();
    unsigned long long frames = 0;

    /*  GAME LOOP */
    while (drawer.window->isOpen())
    {
        drawer.eventHandler(maze, player);

        bool won = maze.hasWon(player, drawer);

        if (!won)
            player.update(drawer, maze);

        sf::Vector2u windowSize = drawer.window->getSize();
        sf::Vector2f center{windowSize.x/2, windowSize.y/2};
        sf::Vector2i mousePos = sf::Mouse::getPosition(*drawer.window);

        auto nowTime = chrono::high_resolution_clock::now();
        float duration = chrono::duration_cast<chrono::milliseconds>(nowTime - startTime).count();
        int fps = ++frames / duration * 1000;

        // Draw & Display
        drawer.clearScreen(sf::Color::White);
        // TODO: 3D rendering
        drawer.drawRectangle({0, 0}, windowSize);
        maze.draw(drawer, sf::Color::Black);
        player.drawVision(drawer, sf::Color::Blue);
        player.draw(drawer, sf::Color::Magenta);

        if (won)
            drawer.drawText("Victory!", windowSize.y/10, center);
        drawer.drawText(to_string(fps), 10, {windowSize.x - 12, 4}, sf::Color::Green);
        drawer.window->display();
    }

    return 0;
}
