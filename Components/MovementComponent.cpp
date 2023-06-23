#include "MovementComponent.h"

//Verwaltet die Bewegung eines Sprites

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
    this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

//functions

const bool MovementComponent::idle() const
{
    if (this->velocity.x == 0.f && this->velocity.y == 0.f)
        return true;

    return false;
}

const bool MovementComponent::moving()
{
    if (this->velocity.x != 0.f || this->velocity.y != 0.f)
        return true;

    return false;
}

const bool MovementComponent::movingLeft()
{
    if (this->velocity.x < 0.f)
        return true;

    return false;
}

const bool MovementComponent::movingRight()
{
    if (this->velocity.x > 0.f)
        return true;

    return false;
}

//update movement component
void MovementComponent::update(const float &deltaTime)
{

    //Deceleration
    if (this->velocity.x > 0.f)
    { //Check for positive x
        //Max velocity check positive
        if (this->velocity.x > maxVelocity)
        {
            this->velocity.x = this->maxVelocity;
        }

        //Deceleration x  positive
        this->velocity.x -= deceleration;
        if (this->velocity.x < 0.f)
        {
            this->velocity.x = 0.f;
        }
    }
    else if (this->velocity.x < 0.f)
    { //Check for negative x
        //Max velocity check x negative
        if (this->velocity.x < -this->maxVelocity)
        {
            this->velocity.x = -this->maxVelocity;
        }
        //Deceleration x negative
        this->velocity.x += deceleration;
        if (this->velocity.x > 0.f)
        {
            this->velocity.x = 0.f;
        }
    }

    if (this->velocity.y > 0.f) //Check for positive y
    {
        //Max velocity check
        if (this->velocity.y > this->maxVelocity)
        {
            this->velocity.y = this->maxVelocity;
        }

        //Deceleration
        this->velocity.y -= deceleration;
        if (this->velocity.y < 0.f)
        {
            this->velocity.y = 0.f;
        }

    }
    else if (this->velocity.y < 0.f)
    { //Check for negative y
        //Max velocity check
        if (this->velocity.y < -this->maxVelocity)
        {
            this->velocity.y = -this->maxVelocity;
        }
        //Deceleration
        this->velocity.y += deceleration;
        if (this->velocity.y > 0.f)
        {
            this->velocity.y = 0.f;
        }
    }

    this->sprite.move(this->velocity * deltaTime); //uses velocity
}

//direction in which the entity is moving
void MovementComponent::move(const float dir_x, const float dir_y, const float &deltaTime)
{
    //Accelerating a sprite unit it reaches max velocity
    //Acceleration
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;

}

//Gibt aktuelle Geschwindigkeit eines Sprites zurück
const sf::Vector2f &MovementComponent::getVelocity() const
{
    return this->velocity;
}




