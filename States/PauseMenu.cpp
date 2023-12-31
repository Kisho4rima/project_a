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
void PauseMenu::update(const sf::Vector2f &mousePos)
{
    for (auto &i : this->buttons)
    {
        i.second->update(mousePos);
    }
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

std::map<std::string, Button *> &PauseMenu::getButtons()
{
    return this->buttons;
}

void PauseMenu::addButtons(const std::string key, float y, const std::string text)
{
    float width = 250.f;
    float height = 50.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new Button(x, y, width, height,
        &this->font, text, 50,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
    return this->buttons[key]->isPressed();
}
