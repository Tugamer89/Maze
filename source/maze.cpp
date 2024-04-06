#include "headers/maze.h"

using namespace std;

Cell::Cell(unsigned int x, unsigned int y) {
    coord = {x, y};
    visited = false;
    walls.top = walls.right = walls.bottom = walls.left = true;
}

Maze::Maze(unsigned int width, unsigned int height) {
    srand(time(NULL));

    dimension = {width, height};
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            maze.push_back(Cell(j, i));

    startCell_index = 0;
    endCell_index = maze.size()-1;
}

size_t Maze::index(int x, int y) {
    if (x < 0 || y < 0 || x >= dimension.x || y >= dimension.y)
        return -1;
    return y * dimension.y + x;
}

bool Maze::randomNeighbor(sf::Vector2i coord, Cell*& choosen) {
    int coords[] = {
        index(coord.x    , coord.y - 1),    // top
        index(coord.x + 1, coord.y    ),    // right
        index(coord.x    , coord.y + 1),    // bottom
        index(coord.x - 1, coord.y    ),    // left
    };

    vector<Cell*> unvisited;
    for (int index : coords)
        if (index > 0 && !maze[index].visited)
            unvisited.push_back(&maze[index]);

    if (unvisited.size() == 0)
        return false;

    choosen = unvisited[rand() % unvisited.size()];
    return true;
}

void Maze::removeWalls(Cell* c1, Cell* c2) {
    int x = c1->coord.x - c2->coord.x;
    int y = c1->coord.y - c2->coord.y;

    if (x == 1) {
        c1->walls.left = false;
        c2->walls.right = false;
    }
    else if (x == -1) {
        c1->walls.right = false;
        c2->walls.left = false;
    }
    else if (y == 1) {
        c1->walls.top = false;
        c2->walls.bottom = false;
    }
    else if (y == -1) {
        c1->walls.bottom = false;
        c2->walls.top = false;
    }
}

/* https://en.wikipedia.org/wiki/Maze_generation_algorithm#Iterative_implementation_(with_stack) */
void Maze::generate() {
    vector<Cell*> stack;

    maze[0].visited = true;
    stack.push_back(&maze[0]);

    while (!stack.empty()) {
        Cell* current = stack.back();
        Cell* choosen = nullptr;
        
        if (randomNeighbor(current->coord, choosen)) {
            removeWalls(current, choosen);
            choosen->visited = true;
            stack.push_back(choosen);
        }
        else
            stack.pop_back();
    }
}

void Maze::draw(Drawer& drawer, sf::Color wallColor, sf::Color cellColor) {
    sf::Vector2u windowSize = drawer.window->getSize();
    int x_dim = windowSize.x / dimension.x;
    int y_dim = windowSize.y / dimension.y;

    for (size_t i = 0; i < maze.size(); ++i) {
        Cell cell = maze[i];

        sf::Vector2u top_left       (cell.coord.x       * x_dim, cell.coord.y       * y_dim);
        sf::Vector2u top_right      ((cell.coord.x + 1) * x_dim, cell.coord.y       * y_dim);
        sf::Vector2u bottom_right   ((cell.coord.x + 1) * x_dim, (cell.coord.y + 1) * y_dim);
        sf::Vector2u bottom_left    (cell.coord.x       * x_dim, (cell.coord.y + 1) * y_dim);
        
        sf::Color color = cellColor;
        if (i == startCell_index)
            color = sf::Color::Green;
        else if (i == endCell_index)
            color = sf::Color::Red;

        drawer.drawRectangle(top_left, bottom_right, color);

        if (cell.walls.top)
            drawer.drawSegment(top_left, top_right, wallColor);
        if (cell.walls.right)
            drawer.drawSegment(top_right, bottom_right, wallColor);
        if (cell.walls.bottom)
            drawer.drawSegment(bottom_right, bottom_left, wallColor);
        if (cell.walls.left)
            drawer.drawSegment(bottom_left, top_left, wallColor);
    }
}
