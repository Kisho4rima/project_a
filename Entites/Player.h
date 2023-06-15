#ifndef PROJECT_A_PLAYER_H
#define PROJECT_A_PLAYER_H

#include "Player.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

//Player class erbt von Entity
class Player :
    public Entity{

public:
    Player(float x, float y, sf::Texture &texture);
    virtual ~Player();

    //Functions
    virtual void update(const float &deltaTime);

private:
    //Variables


    //Ini functions
    void initVariables();
    void initComponents();

};


#endif //PROJECT_A_PLAYER_H
