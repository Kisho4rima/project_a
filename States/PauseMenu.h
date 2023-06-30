#ifndef PROJECT_A_PAUSEMENU_H
#define PROJECT_A_PAUSEMENU_H

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "../Resource Files/Button.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"


class PauseMenu {
public:
    PauseMenu(sf::RenderWindow &window, sf::Font &font);
    ~PauseMenu();

    //functions
    const bool isButtonPressed(const std::string key);
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget *target);
    void addButtons(const std::string key, float y, const std::string text);

    std::map<std::string, Button*> &getButtons();

private:
    sf::Font &font;
    sf::Text menuText;
    sf::RectangleShape background;
    sf::RectangleShape container;
    std::map<std::string, Button*> buttons;

};


#endif //PROJECT_A_PAUSEMENU_H
