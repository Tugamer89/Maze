#include "headers/global.h"

using namespace std;

float distance(sf::Vector2f p1, sf::Vector2f p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

float angleFromVec(sf::Vector2f vec) {
    return M_PI/2 - atan2(vec.x, vec.y);
}

string msToText(float ms) {
    int min = static_cast<int>(ms / 60000);
    ms -= min * 60000;
    int sec = static_cast<int>(ms / 1000);
    ms -= sec * 1000;
    int msInt = static_cast<int>(ms);

    ostringstream ss;
    ss << setfill('0') << setw(2) << min << ":" << setw(2) << sec << "." << setw(3) << msInt;
    
    return ss.str();
}
