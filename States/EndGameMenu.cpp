#include "EndGameMenu.h"


EndGameMenu::EndGameMenu(sf::RenderWindow &window, sf::Font &font, bool victory, float elapsedTime)
        : font(font) {
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

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
    this->endMenuText.setFont(font);
    this->endMenuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->endMenuText.setCharacterSize(60);
    this->endMenuText.setString("");
    this->endMenuText.setPosition(
            this->container.getPosition().x + this->container.getSize().x / 2.f - this->endMenuText.getGlobalBounds().width / 2.f,
            this->container.getPosition().y + 20.f);

    //Time
    this->elapsedTimeText.setFont(font);
    this->elapsedTimeText.setFillColor(sf::Color(255, 255, 255, 200));
    this->elapsedTimeText.setCharacterSize(30); // Setzen Sie die gewünschte Schriftgröße
    std::stringstream ss;
    ss << "Your time: " << elapsedTime;
    this->elapsedTimeText.setString(ss.str());
    this->elapsedTimeText.setPosition(500,500);


    if (victory)
    {
        this->endGameText.setFillColor(sf::Color::Green);
        this->endGameText.setString("Victory!");
    }
    else
    {
        this->endGameText.setFillColor(sf::Color::Red);
        this->endGameText.setString("Defeat!");
    }


}

EndGameMenu::~EndGameMenu()
{
    // Delete the buttons
    auto i = this->buttons.begin();
    for(i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
}

void EndGameMenu::updateInput(const float &dt)
{
    // Handle any input here, such as button clicks
}

void EndGameMenu::update(const sf::Vector2f &mousePos)
{
    for (auto &i : this->buttons)
    {
        i.second->update(mousePos);
    }
}

void EndGameMenu::render(sf::RenderTarget* target)
{
    target->draw(this->background);
    target->draw(this->container);

    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }

    target->draw(this->endGameText);
    target->draw(this->elapsedTimeText);

}

void EndGameMenu::endState()
{
    // Perform any necessary cleanup here
}

void EndGameMenu::updateButtons()
{
    // Update the state of buttons here
}

void EndGameMenu::initKeybinds()
{
    // Initialize any key bindings here
}

void EndGameMenu::initFonts()
{
    if (!this->font.loadFromFile("../Fonts/Commodore Pixelized v1.2.ttf"))
    {
        throw ("ERROR::ENDGAMESTATE::COULD_NOT_LOAD_FONT");
    }
}

void EndGameMenu::initButtons()
{
    // Initialize buttons here
}