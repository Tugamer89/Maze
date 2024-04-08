#pragma once
#include "global.h"

class Drawer;

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
    size_t startCell_index;
    size_t endCell_index;

    size_t index(int x, int y);
    bool randomNeighbor(sf::Vector2i coord, Cell*& choosen);
    void removeWalls(Cell* c1, Cell* c2);

public:
    std::vector<sf::VertexArray> walls;

    Maze(unsigned int width, unsigned int height);
    void generate(Drawer& drawer);
    void calculateWalls(Drawer& drawer);
    sf::Vector2i getStartPos(const Drawer& drawer);
    void draw(Drawer& drawer, sf::Color wallColor);
    bool hasWon(Player& player, Drawer& drawer);
};

