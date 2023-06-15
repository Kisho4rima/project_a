#include "Player.h"
#include <SFML/Graphics.hpp>

//Constructor
Player::Player(float x, float y, sf::Texture &texture_sheet) {

    this->initVariables();
    this->setPosition(x, y);
    this->createMovementComponent(300.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);
    this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 13, 0, 160, 160);

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
    this->animationComponent->play("IDLE_LEFT", deltaTime);
}
