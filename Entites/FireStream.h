#ifndef PROJECT_A_FIRESTREAM_H
#define PROJECT_A_FIRESTREAM_H

#include "../States/GameState.h"
#include "../States/State.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class FireStream {
public:
    FireStream();
    ~FireStream();


    sf::FloatRect getGlobalBounds() const;
    sf::RectangleShape fireStreamShape;
    sf::Texture fireStreamTexture;
    sf::Sprite fireStreamSprite;
    void setActive(bool active);
    void setPosition(float x, float y);
    void render(sf::RenderTarget *target);
    bool isActive() const;

private:
    bool active;
};


#endif //PROJECT_A_FIRESTREAM_H
