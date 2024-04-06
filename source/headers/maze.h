#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include "drawer.h"

class Cell {
public:
    sf::Vector2i coord;
    bool visited;
    struct {
        bool top;
        bool right;
        bool bottom;
        bool left;
    } walls;

    Cell(unsigned int x, unsigned int y);
};

class Maze {
private:
    std::vector<Cell> maze;
    sf::Vector2u dimension;

    size_t index(int x, int y);
    bool randomNeighbor(sf::Vector2i coord, Cell*& choosen);
    void removeWalls(Cell* c1, Cell* c2);

public:
    Maze(unsigned int width, unsigned int height);
    void generate();
    void draw(Drawer& drawer, sf::Color wallColor, sf::Color cellColor);
};

