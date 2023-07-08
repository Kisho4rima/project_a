#ifndef PROJECT_A_GAMESTATE_H
#define PROJECT_A_GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "../Entites/Player.h"
#include "../Entites/Boss.h"
#include "../Components/MovementComponent.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
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
    void updatePauseMenuButtons();
    void update(const float& deltaTime);
    void render(sf::RenderTarget* target = nullptr);


private:
    Player *player;
    Boss *boss;
    PauseMenu *pmenu;
    sf::Font font;

    sf::RectangleShape ground;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    sf::Clock clock;

    sf::Clock gameTime;
    sf::Text timerText;
    sf::Time pausedTime;
    sf::Time timeBeforePause;

    //Functions
    void initKeybinds();
    void initFonts();
    void initBackground();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initGround();
    void checkPlayerCollisionWithGround();
    void checkBossCollisionWithGround();
    void checkPlayerCollisionWithBoss();
    void playTime();

    void initBoss();


    void render(sf::RenderWindow *target);
};


#endif //PROJECT_A_GAMESTATE_H
