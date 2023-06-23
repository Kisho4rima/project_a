//Hauptmenü/Main menue state, wo man das Spiel starten kann, optionen verändern usw.

#ifndef PROJECT_A_MAINMENUSTATE_H
#define PROJECT_A_MAINMENUSTATE_H

#include "GameState.h"
#include "../Resource Files/Button.h"


class MainMenuState :
    public State{
public:
    MainMenuState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State*> *states);
    virtual ~MainMenuState();

    //Functions
    void updateInput(const float &deltaTime);
    void updateButtons();
    void update(const float &deltaTime);
    void renderButtons(sf::RenderTarget *target = nullptr);
    void render(sf::RenderTarget *target = nullptr);


private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
};



#endif //PROJECT_A_MAINMENUSTATE_H
