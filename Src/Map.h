#ifndef PROJECT_A_MAP_H
#define PROJECT_A_MAP_H


#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <cstdio>

class Map
{
public:
    Map();
    ~Map();

    void update();
    void render(sf::RenderWindow *target);

    b2World world_;


private:
    b2BodyDef groundBodyDef;
    b2PolygonShape groundShape;
    b2FixtureDef groundFixtureDef;
    //b2World world;
    b2Body* groundBody_;
    sf::RectangleShape groundShape_;

    void createFixtureForGround();
};




#endif //PROJECT_A_MAP_H
