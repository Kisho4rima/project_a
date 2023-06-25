#ifndef PROJECT_A_GAMESTATE_H
#define PROJECT_A_GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "../Entites/World.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>


class GameState :
        public State
{
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> *states);
    virtual ~GameState();

    //Functions
    void updateInput(const float &deltaTime);
    void updatePlayerInput(const float& deltaTime);
    void update(const float& deltaTime);
    void render(sf::RenderTarget* target = nullptr);


private:
    Player *player;
    World *map;
    PauseMenu *pmenu;
    sf::Font font;

    //Functions
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initCollisionScreen();

    void render(sf::RenderWindow *target);
};


#endif //PROJECT_A_GAMESTATE_H
