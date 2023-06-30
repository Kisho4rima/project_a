#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->initText();
}

SettingsState::~SettingsState()
{
    auto i = this->buttons.begin();
    for(i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
}

void SettingsState::updateInput(const float &deltaTime) {


}

void SettingsState::updateButtons()
{
    //Updated die Buttons im State und Funktionalität
    for (auto &i: this->buttons)
    {
        i.second->update(this->mousePosView);
    }

    //Exit Game
    if (this->buttons["EXIT_STATE"]->isPressed())
    {
        this->endState();
    }

}

void SettingsState::update(const float& deltaTime)
{
    this->updateMousePos();
    this->updateInput(deltaTime);

    this->updateButtons();
}

void SettingsState::renderButtons(sf::RenderTarget *target)
{
    for (auto &i: this->buttons)
    {
        i.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);

    this->renderButtons(target);

    //Remove later
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());

    target->draw(mouseText);
    target->draw(this->optionsText);
}

void SettingsState::initVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                          static_cast<float>(this->window->getSize().y)));

    if(!this->backgroundTexture.loadFromFile("../Assets/Backgrounds/Settings Background.jpg"))
    {
        throw "Error_failed_to_load_main_menu_state_background";
    }
    this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
    if (!this->font.loadFromFile("../Fonts/Commodore Pixelized v1.2.ttf"))
    {
        throw ("Could not load font");
    }
}

void SettingsState::initKeybinds() {

    std::ifstream ifs("../Config/mainmenustate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void SettingsState::initButtons()
{
    this->buttons["EXIT_STATE"] = new Button(1350.f, 1000.f, 250.f, 80.f,
        &this->font, "Quit", 50,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void SettingsState::initText()
{
    this->optionsText.setFont(this->font);

    this->optionsText.setPosition(sf::Vector2f(1350.f, 100.f));
    this->optionsText.setCharacterSize(30);
    this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
    this->optionsText.setString("Resolution \n\nFullscreen \n\nVsynch \n\nAntialiasing \n ");
}


