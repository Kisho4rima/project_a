#include "GameState.h"
#include "../Src/Map.h"

//Constructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> *states)
    : State(window, supportedKeys, states), map(nullptr)
{
    this->map = new Map();
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
}

//Destructor
GameState::~GameState()
{
    delete this->player;
}

void GameState::update(const float& deltaTime)
{
    this->updateMousePos();
    this->updateInput(deltaTime);
    this->player->update(deltaTime);
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    this->player->render(target);

    if (map != nullptr)
    {
        this->map->render(dynamic_cast<sf::RenderWindow *>(target)); // Zeichne die Map
    }

}

void GameState::updateInput(const float &deltaTime)
{
    //Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Left"))))
        this->player->move(-1.f, 0.f, deltaTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Right"))))
        this->player->move(1.f, 0.f, deltaTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Up"))))
        this->player->move(0.f, -1.f, deltaTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Down"))))
        this->player->move(0.f, 1.f, deltaTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->endState();
}

//initializer functions
void GameState::initKeybinds()
{
    std::ifstream ifs("../Config/gamestate_keybinds.ini");

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

void GameState::initTextures()
{
    if (!this->textures["PLAYER_SHEET"].loadFromFile("../Assets/Sprites/Player/IdleAndRun.png")) {
        std::cerr << "ERROR::NON_CRITICAL::GAMESTATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE" << std::endl;
    }
}

void GameState::initPlayers()
{
    this->player = new Player(0,0, this->textures["PLAYER_SHEET"], &this->map->world_);
}




