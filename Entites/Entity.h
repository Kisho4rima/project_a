#ifndef PROJECT_A_ENTITY_H
#define PROJECT_A_ENTITY_H

#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"

class Entity {
public:
    Entity();
    ~Entity();

    //Component functions
    void setTexture(sf::Texture &texture);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture &texture_sheet);

    //Functions
    virtual void setPosition(const float x, const float y);
    //Ich bin nicht sicher ob das nur für den Sprite namens sprite gilt oder auch auf andere Sprites klappen wird.
    virtual void setSpriteSize(sf::Sprite &sprite, float scaleX, float scaleY);
    virtual void move(const float dir_x, const float dir_y, const float deltaTime);
    virtual void update(const float& deltaTime);
    virtual void render(sf::RenderTarget* target);

private:
    void initVariables();

protected:
    sf::Sprite sprite;

    MovementComponent *movementComponent;
    AnimationComponent *animationComponent;
};


#endif //PROJECT_A_ENTITY_H
