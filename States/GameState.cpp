#include "GameState.h"

//Constructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> *states)
    : State(window, supportedKeys, states)
{
    this->initKeybinds();
    this->initFonts();
    this->initBackground();
    this->initTextures();
    this->initPauseMenu();
    this->initPlayers();
    this->initGround();
    this->checkCollision();
}

//Destructor
GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
}

void GameState::update(const float& deltaTime)
{
    this->updateMousePos();
    this->updateKeytime(deltaTime);
    this->updateInput(deltaTime);

    if (!this->paused)
    {
        this->updatePlayerInput(deltaTime);
        this->player->update(deltaTime);
        this->checkCollision();
    }
    else
    {
        this->pmenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }

    // Decrement the jump cooldown
    if (this->player->jumpCooldown > 0.f)
    {
        this->player->jumpCooldown -= deltaTime;
    }
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    this->player->render(target);
    target->draw(this->ground);

    if (this->paused)
    {
        this->pmenu->render(target);
    }
}

void GameState::updatePlayerInput(const float &deltaTime)
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  // Ändern Sie Space zu der Taste, die Sie zum Springen verwenden möchten
    {
        if (this->player->jumpCooldown <= 0.f)
        {
            this->player->jump();
            this->player->jumpCooldown = 1.f;  // Reset the jump cooldown
        }
    }

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

void GameState::initFonts()
{
    if (!this->font.loadFromFile("../Fonts/Commodore Pixelized v1.2.ttf"))
    {
        throw ("Could not load font");
    }
}

void GameState::initBackground()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                          static_cast<float>(this->window->getSize().y)));

    if(!this->backgroundTexture.loadFromFile("../Assets/Backgrounds/MainMenu (1).jpg"))
    {
        throw "Error_failed_to_load_main_menu_state_background";
    }
    this->background.setTexture(&this->backgroundTexture);
}


void GameState::initTextures()
{
    if (!this->textures["PLAYER_SHEET"].loadFromFile("../Assets/Sprites/Player/IdleAndRun.png")) {
        std::cerr << "ERROR::NON_CRITICAL::GAMESTATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE" << std::endl;
    }
}

void GameState::initPlayers()
{
    this->player = new Player(0,0, this->textures["PLAYER_SHEET"]);
}


void GameState::updateInput(const float &deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
    {
        if (!this->paused)
        {
            this->pauseState();
        }
        else
        {
            this->unpauseState();
        }
    }
}

void GameState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButtons("Quit", 900.f, "Quit");
}

void GameState::updatePauseMenuButtons()
{
    if (this->pmenu->isButtonPressed(("Quit")))
    {
        this->endState();
    }
}

void GameState::initGround()
{
    ground.setFillColor(sf::Color::Black);
    ground.setSize(sf::Vector2f(window->getSize().x, 50));
    ground.setPosition(0, window->getSize().y - ground.getSize().y);
}

void GameState::checkCollision()
{   //Wenn der boden und der Player intersecten
    if (this->player->sprite.getGlobalBounds().intersects((this->ground.getGlobalBounds())))
    {
        //std::cout << "Collision occurred" << std::endl; //Hilfe
        this->player->setPosition(this->player->sprite.getPosition().x, this->ground.getPosition().y - this->player->sprite.getGlobalBounds().height);

        //Setzt den Gravitationswert des Spielers
        this->player->gravity = 50000;

        this->player->isJumping = false;
    }
    else
    {
        //std::cout << "No Collision occurd" << std::endl; //Hilfe
        this->player->gravity = 500.8f;
    }
}







