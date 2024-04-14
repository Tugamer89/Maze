#include <iostream>
#include <numeric>
#include <chrono>
#include <queue>
#include "headers/drawer.h"
#include "headers/player.h"
#include "headers/maze.h"
#include "headers/ray.h"

using namespace std;

int main(int argc, char const *argv[]) {
    Drawer drawer(700, 700, "The Tu-Maze");

    Maze maze(15, 15);
    maze.generate(drawer);

    sf::Vector2i startPos = maze.getStartPos(drawer);
    Player player(startPos.x, startPos.y);

    auto oldTime = chrono::high_resolution_clock::now();
    const int FPS_WINDOW_SIZE = 120;
    float totalFrameTime = 0.0f;
    queue<float> frameTimes;

    /*  GAME LOOP */
    while (drawer.window->isOpen())
    {
        drawer.eventHandler(maze, player);

        sf::Vector2u windowSize = drawer.window->getSize();
        sf::Vector2f center{windowSize.x/2, windowSize.y/2};

        bool won = maze.hasWon(player, drawer);
        auto nowTime = chrono::high_resolution_clock::now();
        float duration = chrono::duration_cast<chrono::milliseconds>(nowTime - oldTime).count() / 1000.f;
        oldTime = nowTime;
        int fps;

        if (!won)
            player.update(drawer, maze, duration);
        
        if (duration > 0.0f) {
            frameTimes.push(duration);
            totalFrameTime += duration;

            if (frameTimes.size() > FPS_WINDOW_SIZE) {
                totalFrameTime -= frameTimes.front();
                frameTimes.pop();
            }

            fps = frameTimes.size() / totalFrameTime;
        }

        // Draw & Display
        drawer.clearScreen(sf::Color::White);
        drawer.drawRectangle({0, 0}, {windowSize.x, center.y}, sf::Color::Cyan);
        player.render3D(drawer);
        drawer.drawRectangle({0, 0}, drawer.getMiniMapSize(), sf::Color::White);
        maze.draw(drawer, sf::Color::Black);
        player.drawVision(drawer, sf::Color::Blue);
        player.draw(drawer, sf::Color::Magenta);

        float crossSize = 5.f;
        drawer.drawSegment(sf::Vector2f(center.x - crossSize, center.y), sf::Vector2f(center.x + crossSize, center.y), sf::Color::Red);
        drawer.drawSegment(sf::Vector2f(center.x, center.y - crossSize), sf::Vector2f(center.x, center.y + crossSize), sf::Color::Red);

        if (won)
            drawer.drawText("Victory!", windowSize.y/10, center);
        drawer.drawText(to_string(fps), 10, {windowSize.x - 12, 4}, sf::Color::Black);
        drawer.window->display();
    }

    return 0;
}
