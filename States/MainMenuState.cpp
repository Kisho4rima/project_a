#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> *states)
        : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
};

MainMenuState::~MainMenuState() {

    auto i = this->buttons.begin();
    for(i = this->buttons.begin(); i != this->buttons.end(); ++i){

        delete i->second;
    }


}

void MainMenuState::update(const float& deltaTime) {

    this->updateMousePos();
    this->updateInput(deltaTime);

    this->updateButtons();

}

void MainMenuState::render(sf::RenderTarget* target) {

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

void MainMenuState::updateInput(const float &deltaTime) {


}

void MainMenuState::initKeybinds() {

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

void MainMenuState::initFonts() {

    if (!this->font.loadFromFile("../Fonts/Commodore Pixelized v1.2.ttf")){
        throw ("Could not load font");
    }
}

void MainMenuState::initButtons() {

    /*sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    auto windowWidth = static_cast<float>(desktopMode.width);
    auto windowHeight = static_cast<float>(desktopMode.height);*/



    this->buttons["GAME_STATE"] = new Button(1350.f, 650.f, 250.f, 80.f,
        &this->font, "Start Game", 50,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["SETTINGS"] = new Button(1350, 750, 250, 80,
         &this->font, "Settings", 50,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["EDITOR_STATE"] = new Button(1350, 850, 250, 80,
        &this->font, "Editor", 50,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["EXIT_STATE"] = new Button(1350, 1000, 250, 80,
        &this->font, "Quit", 50,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}

void MainMenuState::updateButtons() {

    //Updated die Buttons im State und Funktionalität
    for (auto &i: this->buttons) {
        i.second->update(this->mousePosView);
    }

    //New Game
    if (this->buttons["GAME_STATE"]->isPressed()) {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

    //Exit Game
    if (this->buttons["EXIT_STATE"]->isPressed()) {
        this->endState();
    }

}

void MainMenuState::renderButtons(sf::RenderTarget *target) {

        for (auto &i: this->buttons) {
            i.second->render(target);
        }

    }

void MainMenuState::initVariables() {

}

void MainMenuState::initBackground(){

    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
        static_cast<float>(this->window->getSize().y)));

    if(!this->backgroundTexture.loadFromFile("../Assets/Backgrounds/background_first.png")){

        throw "Error_failed_to_load_main_menu_state_background";
    }
    this->background.setTexture(&this->backgroundTexture);
}
