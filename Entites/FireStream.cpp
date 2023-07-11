#include "FireStream.h"

FireStream::FireStream()
{
    this->active = false;
    this->fireStreamShape.setSize(sf::Vector2f(2000, 100));
    this->fireStreamShape.setFillColor(sf::Color::Red);

    /*if(!this->fireStreamTexture.loadFromFile("../Assets/Sprites/FireStream/0019.png"))
    {
        std::cout << "Fehler beim Laden der Textur" << std::endl;
    }
    this->fireStreamSprite.setTexture(this->fireStreamTexture);*/
}

FireStream::~FireStream()
{

}

//Position
void FireStream::setPosition(float x, float y)
{
    this->fireStreamShape.setPosition(x, y);
}

//Aktivieren
void FireStream::setActive(bool active)
{
    this->active = active;
}

//Gucken ob es aktiviert ist
bool FireStream::isActive() const
{
        return this->active;
}

//rendern
void FireStream::render(sf::RenderTarget *target)
{
    if (this->active)
    {
        target->draw(this->fireStreamShape);
        /*this->fireStreamSprite.setPosition(this->fireStreamShape.getPosition());
        target->draw(this->fireStreamSprite);*/
    }
}

sf::FloatRect FireStream::getGlobalBounds() const
{
    return this->fireStreamShape.getGlobalBounds();
}