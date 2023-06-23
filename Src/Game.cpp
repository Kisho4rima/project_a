#include "../Header/Game.h"
#include <fstream>
#include <sstream>

//Constructor and Destructor
Game::Game()
{
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while(!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}


//Functions

void Game::endApplication()
{
    std::cout << "End Application\n";
}

void Game::updateDeltaTime()
{
    //Updates deltaTime with the time it takes to update and render one frame
    this->deltaTime = this->deltaTimeClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    //Event polling
    while (this->window->pollEvent(this->ev))
    {
        if (this->ev.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->deltaTime);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear(sf::Color::White);

    //Render items
    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

void Game::run() {

    //Game loop
    while (this->window->isOpen())
    {
        this->updateDeltaTime();
        this->update();
        this->render();
    }


}

//initializer functions

//Window
void Game::initWindow()
{
    //Creating a SFMl window by using the window.ini file
    std::ifstream ifs("../Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();
    std::string title = "project_a";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;

    if(this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
    std::ifstream ifs("../Config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = " ";
        int key_value = 0;

        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

void Game::initVariables()
{
    this->window = NULL;
    this->fullscreen = false;
    this-> deltaTime = 0.f;
}




