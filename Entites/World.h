#ifndef PROJECT_A_WORLD_H
#define PROJECT_A_WORLD_H


#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include <cstdio>

class World
{
public:
    World();
    ~World();

    //functions
    void update();
    void render(sf::RenderWindow *target);

    //world
    b2World world_;


private:
    sf::RectangleShape groundShape_;

    //functions
    void createGround();
};




#endif //PROJECT_A_WORLD_H
