#include "Player.h"
#include "../States/GameState.h"
#include <SFML/Graphics.hpp>



//Constructor
Player::Player(float x, float y, sf::Texture &texture_sheet)
    : jumpCooldown(0.f)
{
    this->initVariables();
    this->setPosition(x, y);
    this->setSpriteSize(sprite, 3.5, 3.5);
    this->createMovementComponent(300.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);
    this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 7, 0, 160, 111);
    this->animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 1, 7, 1, 160, 111);
    this->animationComponent->addAnimation("RUN_RIGHT", 10.f, 0, 2, 7, 2, 160, 111);
    this->animationComponent->addAnimation("RUN_LEFT", 10.f, 0, 3, 7, 3, 160, 111);
    this->gravity = 15000.8f;
    this->jumpForce = -30000.f;
    this->isJumping = false;

}

//Destructor
Player::~Player()
{

}

//Ini Functions
void Player::initVariables()
{

}

void Player::initComponents()
{

}

//Spiel verschiedene Animation je nach Richtung in der die Player läuft/guckt
void Player::update(const float &deltaTime)
{
    this->movementComponent->update(deltaTime);
    this->sprite.move(0, this->gravity * deltaTime);

    if (this->movementComponent->idle())
    {
        if (lastMove == -1)
        {
            this->animationComponent->play("IDLE_LEFT", deltaTime);
        }
        else if (lastMove == 1)
        {
            this->animationComponent->play("IDLE_RIGHT", deltaTime);
        }
    }
    else if (this->movementComponent->movingLeft())
    {
        lastMove = -1;
        this->animationComponent->play("RUN_LEFT", deltaTime);
    }
    else if (this->movementComponent->movingRight())
    {
        lastMove = 1;
        this->animationComponent->play("RUN_RIGHT", deltaTime);
    }

    if (this->isJumping)
    {
        this->sprite.move(0, this->gravity * deltaTime);
        this->gravity += 1000.5f; //Anpassen um Gravitationskraft zu ändern
    }

    // Reduce jump cooldown
    if (this->jumpCooldown > 0.f)
    {
        this->jumpCooldown -= deltaTime;
    }

    // Check for jump input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->jumpCooldown <= 0.f)
    {
        {
            this->isJumping = true;
            this->jumpCooldown = 1.5f; // Set this to the desired cooldown duration in seconds
        }
    }

}

void Player::jump()
{
    if (!this->isJumping)
    {
        this->isJumping = false;
        this->gravity = this->jumpForce; // Weise der y-Beschleunigung die Sprungkraft zu
    }
}








