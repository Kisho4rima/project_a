#include "EndScreen.h"

EndScreen::EndScreen(sf::RenderWindow *window, sf::Font &font)
    : font(font)
{
    //Background
    this->background.setSize(sf::Vector2f(
            static_cast<float >(window->getSize().x),
            static_cast<float >(window->getSize().y)));
    this->background.setFillColor(sf::Color(20, 20, 20, 100));

    //Container
    this->container.setSize(sf::Vector2f(
            static_cast<float >(window->getSize().x / 4.f),
            static_cast<float >(window->getSize().y - 400.f)));
    this->container.setFillColor(sf::Color(0, 20, 20, 200));
    this->container.setPosition(static_cast<float >(window->getSize().x / 1.f - this->container.getSize().x) / 2.f, 30.f);

    this->setMenuText("PLACEHOLDER");

}

EndScreen::~EndScreen()
{
    auto i = this->buttons.begin();
    for(i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
}

//functions
void EndScreen::update(const sf::Vector2f &mousePos)
{
    for (auto &i : this->buttons)
    {
        i.second->update(mousePos);
    }
}

void EndScreen::render(sf::RenderTarget *target)
{
    target->draw(this->background);
    target->draw(this->container);

    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }

    target->draw(this->menuText);
    target->draw(this->requiredTime);
}

std::map<std::string, Button *> &EndScreen::getButtons()
{
    return this->buttons;
}

void EndScreen::addButtons(const std::string key, float y, const std::string text)
{
    float width = 250.f;
    float height = 50.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new Button(x, y, width, height,
                                    &this->font, text, 50,
                                    sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                                    sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons[key] = new Button(x, y, width, height,
                                    &this->font, text, 50,
                                    sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                                    sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));


}

const bool EndScreen::isButtonPressed(const std::string key)
{
    return this->buttons[key]->isPressed();
}

void EndScreen::setMenuText(const std::string text)
{
    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(60);
    this->menuText.setString(text);
    this->menuText.setPosition(
            this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
            this->container.getPosition().y + 20.f);

    // Set different colors for "victory" and "defeat"
    if (text == "VICTORY") {
        this->menuText.setFillColor(sf::Color::Green);  // Green for victory
    } else if (text == "DEFEAT") {
        this->menuText.setFillColor(sf::Color::Red);  // Red for defeat
    } else {
        this->menuText.setFillColor(sf::Color::White);  // Default color
    }
}

void EndScreen::setRequiredTime(float timeInSeconds)
{
    this->requiredTime.setFont(font);
    this->requiredTime.setCharacterSize(35);
    std::string timeStr = std::to_string(timeInSeconds);
    this->requiredTime.setString("Required Time: \n" + timeStr + " seconds");
    this->requiredTime.setPosition(
            this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
            this->container.getPosition().y + 200.f);
}
