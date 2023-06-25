#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> *states)
        : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
};

EditorState::~EditorState()
{
    auto i = this->buttons.begin();
    for(i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
}

void EditorState::update(const float& deltaTime)
{
    this->updateMousePos();
    this->updateInput(deltaTime);

    this->updateButtons();
}

void EditorState::render(sf::RenderTarget* target)
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
}

void EditorState::updateInput(const float &deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->endState();
}

void EditorState::initKeybinds() {

    std::ifstream ifs("../Config/editorstate_keybinds.ini");

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

void EditorState::initFonts()
{
    if (!this->font.loadFromFile("../Fonts/Commodore Pixelized v1.2.ttf"))
    {
        throw ("Error::EditorState: Could not load font");
    }
}

void EditorState::initButtons()
{

}

void EditorState::updateButtons()
{
    //Updated die Buttons im State und Funktionalität
    for (auto &i: this->buttons)
    {
        i.second->update(this->mousePosView);
    }
}

void EditorState::renderButtons(sf::RenderTarget *target)
{
    for (auto &i: this->buttons)
    {
        i.second->render(target);
    }
}

void EditorState::initVariables()
{

}

void EditorState::initBackground()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                          static_cast<float>(this->window->getSize().y)));

    if(!this->backgroundTexture.loadFromFile("../Assets/Backgrounds/editorstate_background.jpg"))
    {
        throw "Error_failed_to_load_editor_state_background";
    }
    this->background.setTexture(&this->backgroundTexture);
}