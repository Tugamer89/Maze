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
void Maze::generate(Drawer& drawer) {
    stack<Cell*> stack;

    maze[0].visited = true;
    stack.push(&maze[0]);

    while (!stack.empty()) {
        Cell* current = stack.top();
        Cell* choosen = nullptr;
        
        if (randomNeighbor(current->coord, choosen)) {
            removeWalls(current, choosen);
            choosen->visited = true;
            stack.push(choosen);
        }
        else
            stack.pop();
    }

    calculateWalls(drawer);
}

// TODO: optimize number of walls
void Maze::calculateWalls(Drawer& drawer) {
    walls.clear();

    sf::Vector2u windowSize = drawer.window->getSize();
    int x_dim = windowSize.x / dimension.x;
    int y_dim = windowSize.y / dimension.y;

    for (size_t i = 0; i < maze.size(); ++i) {
        Cell cell = maze[i];

        sf::Vector2f top_left       (cell.coord.x       * x_dim, cell.coord.y       * y_dim);
        sf::Vector2f top_right      ((cell.coord.x + 1) * x_dim, cell.coord.y       * y_dim);
        sf::Vector2f bottom_right   ((cell.coord.x + 1) * x_dim, (cell.coord.y + 1) * y_dim);
        sf::Vector2f bottom_left    (cell.coord.x       * x_dim, (cell.coord.y + 1) * y_dim);

        sf::VertexArray wall(sf::Lines, 2);

        if (cell.walls.top) {
            wall[0] = top_left;
            wall[1] = top_right;
            walls.push_back(wall);
        }
        if (cell.walls.right) {
            wall[0] = top_right;
            wall[1] = bottom_right;
            walls.push_back(wall);
        }
        if (cell.walls.bottom) {
            wall[0] = bottom_right;
            wall[1] = bottom_left;
            walls.push_back(wall);
        }
        if (cell.walls.left) {
            wall[0] = bottom_left;
            wall[1] = top_left;
            walls.push_back(wall);
        }
    }
}

sf::Vector2i Maze::getStartPos(const Drawer& drawer) {
    sf::Vector2u windowSize = drawer.window->getSize();
    int x_dim = windowSize.x / dimension.x;
    int y_dim = windowSize.y / dimension.y;

    int x = maze[startCell_index].coord.x * x_dim + x_dim/2;
    int y = maze[startCell_index].coord.y * y_dim + y_dim/2;

    return {x, y};
}

void Maze::draw(Drawer& drawer, sf::Color wallColor) {
    sf::Vector2u windowSize = drawer.window->getSize();
    int x_dim = windowSize.x / dimension.x;
    int y_dim = windowSize.y / dimension.y;

    for (size_t i : {startCell_index, endCell_index}) {
        Cell cell = maze[i];

        sf::Vector2u top_left       (cell.coord.x       * x_dim, cell.coord.y       * y_dim);
        sf::Vector2u bottom_right   ((cell.coord.x + 1) * x_dim, (cell.coord.y + 1) * y_dim);

        if (i == startCell_index)
            drawer.drawRectangle(top_left, bottom_right, sf::Color::Red);
        else if (i == endCell_index)
            drawer.drawRectangle(top_left, bottom_right, sf::Color::Green);
    }

    for (sf::VertexArray wall : walls)
        drawer.drawSegment(wall[0].position, wall[1].position, wallColor);
}

bool Maze::hasWon(Player& player, Drawer& drawer) {
    sf::Vector2u windowSize = drawer.window->getSize();
    int x_dim = windowSize.x / dimension.x;
    int y_dim = windowSize.y / dimension.y;

    sf::Vector2u top_left       (maze[endCell_index].coord.x       * x_dim, maze[endCell_index].coord.y       * y_dim);
    sf::Vector2u bottom_right   ((maze[endCell_index].coord.x + 1) * x_dim, (maze[endCell_index].coord.y + 1) * y_dim);    

    return player.coord.x > top_left.x && player.coord.x < bottom_right.y && 
           player.coord.y > top_left.y && player.coord.y < bottom_right.y;
}
