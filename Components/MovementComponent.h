#ifndef PROJECT_A_MOVEMENTCOMPONENT_H
#define PROJECT_A_MOVEMENTCOMPONENT_H

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

//Create a movement component, add it to the entity and check in the entity if it has a movement component
//,and then it will be possible to move the entity


class MovementComponent {
public:
    MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);
    ~MovementComponent();

    //Accessor
    const sf::Vector2f &getVelocity() const;

    //functions
    const bool idle() const;
    void move(const float x, const float y, const float &deltaTime);
    void update(const float &deltaTime);


private:
    sf::Sprite &sprite;

    //direction and speed
    float maxVelocity;

    sf::Vector2f velocity;
    float acceleration;
    float deceleration;

    //Initializer functions


};


#endif //PROJECT_A_MOVEMENTCOMPONENT_H
