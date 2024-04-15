#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <stack>
#include "drawer.h"
#include "player.h"
#include "maze.h"
#include "ray.h"

class Ray;
class Maze;
class Drawer;
class Player;

float distance(sf::Vector2f p1, sf::Vector2f p2);
float angleFromVec(sf::Vector2f vec);
std::string msToText(float milliseconds);
