#include "Map.h"

Map::Map() : world_(b2Vec2(0.0f, 9.81f))
{
    //b2Vec2 gravity(0.0f, 9.81f);

    //erstellt Körper
    groundBody_ = world_.CreateBody(&groundBodyDef);
    //Position
    groundBodyDef.position.Set(0.0f, 50.0f);

    //Kollision
    groundFixtureDef.shape = &groundShape;
    groundBody_->CreateFixture(&groundFixtureDef);

    groundShape_.setSize(sf::Vector2f(3000.0f, 70.0f));
    groundShape_.setPosition(0.0f, 1550.0f);
    groundShape_.setFillColor(sf::Color::Black);

    createFixtureForGround();
}

//draw Körper

void Map::render(sf::RenderWindow *target)
{
    target->draw(groundShape_);
}

void Map::createFixtureForGround()
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;

    groundBody_->CreateFixture(&fixtureDef);
}




