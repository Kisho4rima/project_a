#include "Entity.h"

Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
    delete this->movementComponent;
    delete this->animationComponent;
}

void Entity::move(const float dir_x, const float dir_y, const float deltaTime)
{
    if (this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, deltaTime); //sets velocity
    }
}

void Entity::update(const float &deltaTime)
{

}

void Entity::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}

//Component functions
void Entity::setTexture(sf::Texture &texture)
{
    this->sprite.setTexture(texture);
}

void Entity::initVariables()
{
    this->movementComponent = NULL;
}

void Entity::setPosition(const float x, const float y)
{
        this->sprite.setPosition(x, y);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::setSpriteSize(sf::Sprite &sprite, float scaleX, float scaleY)
{
    sprite.setScale(scaleX, scaleY);
    //sprite.setTextureRect(sf::Rect(scaleX, scaleY));
}


