#include "Player.h"
#include <SFML/Graphics.hpp>

//Constructor
Player::Player(float x, float y, sf::Texture &texture_sheet) {

    this->initVariables();
    this->setPosition(x, y);
    this->createMovementComponent(300.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);
    this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 7, 0, 160, 111);
    this->animationComponent->addAnimation("RUN_LEFT", 10.f, 0, 1, 7, 1, 160, 111);

}

//Destructor
Player::~Player() {

}

//Ini Functions
void Player::initVariables() {

}

void Player::initComponents() {


}

void Player::update(const float &deltaTime) {

    this->movementComponent->update(deltaTime);

    if (this->movementComponent->idle())
        this->animationComponent->play("IDLE_LEFT", deltaTime);
    else
        this->animationComponent->play("RUN_LEFT", deltaTime);

}

void Player::setSpriteSize(sf::Sprite &sprite, float scaleX, float scaleY) {

    sprite.setScale(scaleX, scaleY);

}
