#ifndef PROJECT_A_ENDGAMEMENU_H
#define PROJECT_A_ENDGAMEMENU_H

#include "../Resource Files/Button.h"
#include "PauseMenu.h"
#include "State.h"
#include "GameState.h"


class EndGameMenu {
public:
    EndGameMenu(sf::RenderWindow &window, sf::Font &font, bool victory, float elapsedTime);
    virtual ~EndGameMenu();

    // Functions
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget* target);
    void endState();
    void updateInput(const float &dt);
    void updateButtons();

private:
    sf::Font font;
    sf::Text endGameText; // Diese Variable hält den Endgame-Status (Victory oder Defeat)
    std::map<std::string, Button*> buttons;
    sf::RectangleShape background;
    sf::RectangleShape container;
    sf::Text endMenuText;
    sf::Text elapsedTimeText; //Gibt Zeit im endMenu an


    void initKeybinds();
    void initFonts();
    void initButtons();

};


#endif //PROJECT_A_ENDGAMEMENU_H
