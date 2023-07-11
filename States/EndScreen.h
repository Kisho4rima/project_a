#ifndef PROJECT_A_ENDSCREEN_H
#define PROJECT_A_ENDSCREEN_H

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

class EndScreen {
public:
    EndScreen(sf::RenderWindow* window, sf::Font &font);
    ~EndScreen();

    const bool isButtonPressed(const std::string key);
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget *target);
    void addButtons(const std::string key, float y, const std::string text);
    void setMenuText(const std::string text);
    void setRequiredTime(float timeInSeconds);
    std::map<std::string, Button*> &getButtons();

    sf::Text menuText;
    sf::Text requiredTime;

private:
    sf::Font &font;
    sf::RectangleShape background;
    sf::RectangleShape container;
    std::map<std::string, Button*> buttons;

};


#endif //PROJECT_A_ENDSCREEN_H
