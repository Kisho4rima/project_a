#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font)
    : font(font)
{
    //Background
    this->background.setSize(sf::Vector2f(
        static_cast<float >(window.getSize().x),
        static_cast<float >(window.getSize().y)));
    this->background.setFillColor(sf::Color(20, 20, 20, 100));

    //Container
    this->container.setSize(sf::Vector2f(
        static_cast<float >(window.getSize().x / 4.f),
        static_cast<float >(window.getSize().y - 400.f)));
    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(static_cast<float >(window.getSize().x / 1.f - this->container.getSize().x) / 2.f, 30.f);

    //Text
    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(60);
    this->menuText.setString("PAUSED");
    this->menuText.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 20.f);


}

PauseMenu::~PauseMenu()
{
    auto i = this->buttons.begin();
    for(i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
}

//functions
void PauseMenu::update()
{

}

void PauseMenu::render(sf::RenderTarget *target)
{
    target->draw(this->background);
    target->draw(this->container);

    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }

    target->draw(this->menuText);
}
