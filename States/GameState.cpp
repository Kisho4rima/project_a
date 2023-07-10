#include "GameState.h"
#include <sstream>
#include <iomanip>

//Constructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> *states)
    : State(window, supportedKeys, states)
{
    this->initKeybinds();
    this->initFonts();
    this->initBackground();
    this->initTextures();
    this->initPauseMenu();
    this->initEndScreen();
    this->initPlayers();
    this->initGround();
    this->checkPlayerCollisionWithGround();
    this->initBoss();
    this->checkBossCollisionWithGround();
    this->playTime();

    this->timerText.setFont(font);
    this->timerText.setCharacterSize(24);
    this->timerText.setFillColor(sf::Color::Black);
    this->timerText.setPosition(sf::Vector2f(this->window->getSize().x / 2 - 140, 60.f));
    this->timerText.setScale(3.f, 3.f);

    //Boss name
    this->boss->bossName.setFillColor(sf::Color::White);
    this->boss->bossName.setString("FIRE DEMON");
    this->boss->bossName.setPosition(sf::Vector2f(2500, 50));
    this->boss->bossName.setFont(font);

    //Player Name
    this->player->playerName.setFillColor(sf::Color::White);
    this->player->playerName.setString("RYUEN");
    this->player->playerName.setPosition(sf::Vector2f(100, 50));
    this->player->playerName.setFont(font);

    this->gameJustEnded = false;
    this->victoryThemeStarted = false;
    this->defeatThemeStarted = false;

}

//Destructor
GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
    delete this->boss;
    //delete this->endGameMenu;
}

void GameState::update(const float& deltaTime)
{
    this->updateMousePos();
    this->updateKeytime(deltaTime);
    this->updateInput(deltaTime);
    //pausedTime += gameTime.getElapsedTime() - timeBeforePause;

    if (!this->paused)
    {
        float currentTime = this->clock.getElapsedTime().asSeconds();

        this->updatePlayerInput(deltaTime);
        this->player->update(deltaTime);
        this->boss->update(*this->player, deltaTime, currentTime);
        this->checkPlayerCollisionWithGround();
        this->checkBossCollisionWithGround();
        this->playTime();
        sf::Time elapsed = gameTime.getElapsedTime() - pausedTime;

        this->player->updateHealthBar(this->player->healthBar);
        this->player->attack(this->boss);
        this->boss->updateHealthBar(this->boss->bossHealthBar);

        this->endScreen->update(this->mousePosView);
        this->updateEndScreenButtons();
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

    //Um die Zeit zu kriegen die man dann im EndScreen anzeigen kann
    if ((this->player->isDying || this->boss->isDying) && !this->gameJustEnded)
    {
        this->gameEndTime = this->gameTime.getElapsedTime().asSeconds();
        this->endScreen->setRequiredTime(this->gameEndTime);
        this->gameJustEnded = true;
    }

    //Je nachdem ob der Boss oder Player gewinnt, steht da dann Victory oder defeat
    if (!victoryTheme.openFromFile("../soundtrack/victoryTheme.wav"))
    {
        std::cout << "Could not load victoryTheme";
    }
    if (!defeatTheme.openFromFile("../soundtrack/defeatTheme.wav"))
    {
        std::cout << "could not load defeatTheme";
    }

    if (this->player->isDying)
    {
        this->defeatTheme.play();
        this->defeatThemeStarted = true;
    }
    else if (this->boss->isDying)
    {
        this->victoryTheme.play();
        this->victoryThemeStarted = true;
    }

}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }
    target->draw(this->ground);
    target->draw(this->background);
    this->player->render(target);
    this->boss->render(target);
    target->draw(this->player->collisionBox);
    target->draw(this->boss->collisionBoxBoss);
    target->draw(this->boss->attackCollisionBox);
    target->draw(this->boss->pushBackCollision);
    target->draw(this->player->playerName);
    target->draw(this->player->healthBar);
    target->draw(this->timerText);
    target->draw(this->boss->bossName);
    target->draw(this->boss->bossHealthBar);
    target->draw(this->player->hitbox);


    if (this->paused)
    {
        this->pmenu->render(target);
    }

    if (this->player->isDying)
    {
        this->endScreen->setMenuText("DEFEAT");
        this->endScreen->render(this->window);
    }
    else if (this->boss->isDying)
    {
        this->endScreen->setMenuText("VICTORY");
        this->endScreen->render(this->window);
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

    if(!this->backgroundTexture.loadFromFile("../Assets/Backgrounds/GamState.jpg"))
    {
        throw "Error_failed_to_load_main_menu_state_background";
    }
    this->background.setTexture(&this->backgroundTexture);
}


void GameState::initTextures()
{
    if (!this->textures["PLAYER_SHEET"].loadFromFile("../Assets/Sprites/Player/Fire_WarriorFireSword-Sheet.png")) {
        std::cerr << "ERROR::NON_CRITICAL::GAMESTATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE" << std::endl;
    }

    if (!this->textures["BOSS_SHEET"].loadFromFile("../Assets/Sprites/Boss/boss_idle.png"))
    {
        std::cerr << "ERROR::NON_CRITICAL::GAMESTSTATE::COULD_NOT_LOAD_BOSS_TEXTURE" << std::endl;
    }
}

void GameState::initPlayers()
{
    this->player = new Player(0,0, this->textures["PLAYER_SHEET"]);
}

void GameState::initBoss()
{
    this->boss = new Boss(0, 00, this->textures["BOSS_SHEET"]);
}


void GameState::updateInput(const float &deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
    {
        if (!this->paused)
        {
            this->pauseState();
            this->timeBeforePause = gameTime.getElapsedTime();  // Speichern Sie den Zeitpunkt der Pause
        }
        else
        {
            this->unpauseState();
            this->pausedTime += gameTime.getElapsedTime() - this->timeBeforePause;  // Addieren Sie die Dauer der Pause zur Gesamtpausenzeit
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

void GameState::initEndScreen()
{
    this->endScreen = new EndScreen(this->window, this->font);

    this->endScreen->addButtons("Try Again", 800.f, "Try Again");

    this->endScreen->addButtons("Quit", 900.f, "Quit");
}

void GameState::updateEndScreenButtons()
{
    if (this->endScreen->isButtonPressed(("Quit")))
    {
        this->endState();
    }

    if (this->endScreen->isButtonPressed("Try Again"))
    {
        this->endState();
        // Erstelle einen neuen GameState
        this->states->push(new GameState(window, supportedKeys, states));
    }
}


void GameState::initGround()
{
    ground.setFillColor(sf::Color::Black);
    ground.setSize(sf::Vector2f(window->getSize().x, 50));
    ground.setPosition(0, window->getSize().y - ground.getSize().y);
}

void GameState::checkPlayerCollisionWithGround()
{
    sf::Rect<float> playerCollisionBox = this->player->collisionBox.getGlobalBounds();
    sf::Rect<float> groundBox = this->ground.getGlobalBounds();

    if (playerCollisionBox.intersects(groundBox))
    {
        float offsetY = this->player->collisionBox.getPosition().y - this->player->sprite.getPosition().y;
        this->player->setPosition(this->player->sprite.getPosition().x, groundBox.top - playerCollisionBox.height - offsetY);

        this->player->gravity = 500;
        this->player->isJumping = false;
    }
    else
    {
        this->player->gravity = 500.8f;
    }
}

void GameState::checkBossCollisionWithGround()
{
    sf::Rect<float> bossCollisionBox = this->boss->collisionBoxBoss.getGlobalBounds();
    sf::Rect<float> groundBox = this->ground.getGlobalBounds();

    if (bossCollisionBox.intersects(groundBox))
    {
        float offsetY = this->boss->collisionBoxBoss.getPosition().y - this->boss->sprite.getPosition().y;
        this->boss->setPosition(this->boss->sprite.getPosition().x, groundBox.top - bossCollisionBox.height - offsetY);
    }
}

void GameState::checkPlayerCollisionWithBoss()
{
    sf::Rect<float> playerCollisionBox = this->player->collisionBox.getGlobalBounds();
    sf::Rect<float> bossCollisionBox = this->boss->collisionBoxBoss.getGlobalBounds();

    if (playerCollisionBox.intersects(bossCollisionBox))
    {

    }
}

void GameState::playTime()
{
    sf::Time elapsed = gameTime.getElapsedTime() - pausedTime;
    int seconds = elapsed.asSeconds();
    int minutes = seconds / 60;
    seconds %= 60;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << minutes;
    ss << ":";
    ss << std::setw(2) << std::setfill('0') << seconds;

    timerText.setString(ss.str());
}












