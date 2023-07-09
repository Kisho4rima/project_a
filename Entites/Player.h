#ifndef PROJECT_A_PLAYER_H
#define PROJECT_A_PLAYER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Boss.h"

class Boss;

//Player class erbt von Entity
class Player :
    public Entity{

public:
    Player(float x, float y, sf::Texture &texture);
    virtual ~Player();

    float gravity;
    float jumpForce;
    bool isJumping;
    float jumpCooldown;

    //Functions
    virtual void update(const float &deltaTime);
    void jump();
    void pushback();


    void takeDamage(int damage);
    int playerHealth;
    float damageCoolDown;
    sf::Clock gameClock;
    sf::RectangleShape healthBar;
    void updateHealthBar(sf::RectangleShape &healthBar);
    int getHealth();

    sf::Text playerName;

    sf::RectangleShape collisionBox;

    sf::Vector2f getPosition() const;

    void createHitbox();
    sf::RectangleShape hitbox;
    void destroyHitbox();
    int attackDamage;
    void attack(Boss *boss);




private:
    //Variables
    sf::Vector2f playerSize;

    void death();


    /*Dient dazu, um die ausrichtung des Sprites zu erkennen und je nachdem die idle animation in die Richtung abzuspielen,
    der die der Sprite schaut*/
    int lastMove;
    float attackCooldown; //Cooldown zwischen Angriffen
    float attackTimer; //Timer für den Angriff

    bool isInContactWithBoss;

    //Ini functions
    void initVariables();
    void initComponents();


protected:

};


#endif //PROJECT_A_PLAYER_H
