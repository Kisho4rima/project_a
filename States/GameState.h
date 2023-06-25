#ifndef PROJECT_A_GAMESTATE_H
#define PROJECT_A_GAMESTATE_H

#include "State.h"
#include "../Entites/World.h"

class GameState :
        public State
{
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> *states);
    virtual ~GameState();

    //Functions
    void updateInput(const float& deltaTime);
    void update(const float& deltaTime);
    void render(sf::RenderTarget* target = nullptr);


private:
    Player *player;
    World *map;

    //Functions
    void initKeybinds();
    void initTextures();
    void initPlayers();

    void render(sf::RenderWindow *target);
};


#endif //PROJECT_A_GAMESTATE_H
