#include "Player.h"
#include "../States/GameState.h"
#include <SFML/Graphics.hpp>


//Constructor
Player::Player(float x, float y, sf::Texture &texture_sheet, b2World *world)
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
    this->world = world;
    this->initPlayerFixture();
    this->initPlayerBody();
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
}

void Player::initPlayerFixture()
{
    //Erstellen einen Polygon der über den Sprite gelegt wird
    b2PolygonShape sShape;
    sShape.SetAsBox(sprite.getGlobalBounds().width / 3.5, sprite.getGlobalBounds().height / 3.5f);
    //Erstelle Fixture für Kollision
    b2FixtureDef fixtureDef;
    fixtureDef.shape =  &sShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;

    //Füge die Fixture dem Körper des Spielers hinzu
    //bodyDef->CreateFixture(&fixtureDef);

}

void Player::initPlayerBody()
{
    //Erstellung des Bodys
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(3.f, 3.f); //Keine Ahnung welche Koordinaten eigentlich rein müssen
    b2Body* dynamicBody = world->CreateBody(&playerBodyDef);
}





