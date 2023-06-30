#ifndef PROJECT_A_SETTINGSSTATE_H
#define PROJECT_A_SETTINGSSTATE_H

#include "State.h"
#include "../Resource Files/Button.h"

class SettingsState : public State {
public:
    SettingsState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State*> *states);
    virtual ~SettingsState();

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

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initText();

};


#endif //PROJECT_A_SETTINGSSTATE_H
