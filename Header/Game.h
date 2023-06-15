#ifndef PROJECT_A_GAME_H
#define PROJECT_A_GAME_H

#include "../States/MainMenuState.h"



class Game{

public:
    //Constructor / Destructor
    Game();
    virtual ~Game();

    //Functions

    //Regular Functions
    void endApplication();

    //Update
    void updateDeltaTime();
    void updateSFMLEvents();
    void update();

    //Render
    void render();

    //Core
    void run();



private:

    //Variables
    sf::RenderWindow *window;
    sf::Event ev;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen;

    sf::Clock deltaTimeClock;
    float deltaTime;

    //State stack
    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    //initializer functions
    void initVariables();
    void initWindow();
    void initKeys();
    void initStates();


};


#endif //PROJECT_A_GAME_H
