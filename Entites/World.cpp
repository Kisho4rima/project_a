#include "World.h"

World::World() : world_(b2Vec2(0.0f, 9.81f))
{
    b2Vec2 gravity(0.0f, 9.81f);

    this->createGround();
}

World::~World()
{

}

//draw Körper

void World::render(sf::RenderWindow *target)
{
    target->draw(groundShape_);
}

void World::createGround()
{
    //Position
    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0.0f, 1550.0f);

    b2Body *groundBody_ = world_.CreateBody(&groundBodyDef);;

    b2PolygonShape groundShape;
    groundShape.SetAsBox(3000.f, 20.f);

    //Kollision
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundBody_->CreateFixture(&groundFixtureDef);

    groundShape_.setSize(sf::Vector2f(3000.0f, 70.0f));
    groundShape_.setPosition(0.0f, 1550.0f);
    groundShape_.setFillColor(sf::Color::Black);
}








