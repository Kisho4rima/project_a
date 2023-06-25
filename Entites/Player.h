#ifndef PROJECT_A_PLAYER_H
#define PROJECT_A_PLAYER_H

#include "Player.h"
#include "Entity.h"
#include "World.h"
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

//Player class erbt von Entity
class Player :
    public Entity{

public:
    Player(float x, float y, sf::Texture &texture, b2World *world);
    virtual ~Player();

    //Functions
    virtual void update(const float &deltaTime);

private:
    //Variables
    b2World *world;// Zeiger auf die b2World instanz
    sf::Vector2f playerSize;


    /*Dient dazu, um die ausrichtung des Sprites zu erkennen und je nachdem die idle animation in die Richtung abzuspielen,
    der die der Sprite schaut*/
    int lastMove;

    //Ini functions
    void initVariables();
    void initComponents();
    void initPlayerBody();
    void initPlayerFixture();
    void initPlayerCollision();

protected:

};


#endif //PROJECT_A_PLAYER_H
