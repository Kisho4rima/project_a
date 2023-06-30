#ifndef PROJECT_A_BUTTON_H
#define PROJECT_A_BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

enum button_states{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button {
public:
    Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size,
        sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
        sf::Color idle_color, sf::Color hover_color, sf::Color active_color);

    ~Button();

    //Accessor returnt den boolean Wert, entsprechend dem Button State
    const bool isPressed() const;

    //Functions
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget *target);

private:
    short unsigned buttonState;
    bool pressed;
    bool hover;

    sf::RectangleShape bShape;
    sf::Font *font;
    sf::Text text;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

};


#endif //PROJECT_A_BUTTON_H
