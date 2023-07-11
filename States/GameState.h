#ifndef PROJECT_A_GAMESTATE_H
#define PROJECT_A_GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "EndScreen.h"
#include "../Entites/Player.h"
#include "../Entites/Boss.h"
#include "../Entites/FireStream.h"
#include "../Components/MovementComponent.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>


class FireStream;

class GameState :
        public State
{
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> *states, sf::Music &music);
    virtual ~GameState();

    //Functions
    void updateInput(const float &deltaTime);
    void updatePlayerInput(const float& deltaTime);
    void updatePauseMenuButtons();
    void updateEndScreenButtons();
    void update(const float& deltaTime);
    void render(sf::RenderTarget* target = nullptr);

    float gameEndTime;
    bool gameJustEnded;
    bool gameOver;    //handled die FireStreams, damit die nachdem man try again drückt wieder genereiert werden




private:
    Player *player;
    Boss *boss;
    PauseMenu *pmenu;
    sf::Font font;
    EndScreen *endScreen;


    sf::RectangleShape ground;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    sf::Clock clock;
    sf::Clock gameTime;
    sf::Text timerText;
    sf::Time pausedTime;
    sf::Time timeBeforePause;
    sf::Clock deltaTimeClock;

    //Sound
    sf::Music &backgroundTheme;


    bool victoryThemeStarted;
    bool defeatThemeStarted;

    std::vector<FireStream> fireStreams;
    float fireStreamTimer;
    float fireStreamSpawnInterval;
    int activeFireStreamIndex;
    int FIRESTREAM_WIDTH;
    int FIRESTREAM_HEIGHT;

    //Functions
    void initKeybinds();
    void initFonts();
    void initBackground();
    void initTextures();
    void initPauseMenu();
    void initEndScreen();
    void initPlayers();
    void initGround();
    void checkPlayerCollisionWithGround();
    void checkBossCollisionWithGround();
    void checkPlayerCollisionWithBoss();
    void playTime();
    void render(sf::RenderWindow *target);
    void initBoss();
    void updateFireStreams();
};


#endif //PROJECT_A_GAMESTATE_H
