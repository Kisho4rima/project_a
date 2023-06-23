#ifndef PROJECT_A_ANIMATIONCOMPONENT_H
#define PROJECT_A_ANIMATIONCOMPONENT_H

#include <map>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

/*Die AnimationComponent Klasse wird zum Animieren des Sprites verwendet*/

class AnimationComponent {
public:
    AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet);
    ~AnimationComponent();

    //Functions

    /*Hinzufügen einer Animation zur AnimationComponent
    Erfordert einen Key, Animationsdauer und Parameter um, um den Rahmenbereich und die Größe der Frames in der
    Textur festzulegen*/
    void addAnimation(const std::string key,
        float animation_timer,
        int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

    /*Spielt die Animation basierend auf dem angegebenen Key ab. Aktualisiert die Animation des Sprites in regelmäßigen
    Abständen basierend auf der deltaTime*/
    void play(const std::string  key, const float &deltaTime);


private:
    //Interne Klasse repräsentiert eine Animation.
    //Enthält Informationen wie Sprite- und Texturen verweise, Animationsdauer, Rahmenbereich und aktueller Rahmen.
    class Animation{
    public:
        //Variables
        sf::Sprite &sprite;
        sf::Texture &textureSheet;
        float animationTimer;
        float timer;
        int width;
        int height;
        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;


        Animation(sf::Sprite &sprite, sf::Texture &texture_sheet,
            float animation_timer,
            int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
            : sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height)
                {
                    this->timer = 0.f;
                    this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
                    this->currentRect = this->startRect;
                    this->endRect = sf::IntRect (frames_x * width, frames_y * height, width, height);
                    this->sprite.setTexture(this->textureSheet, true);
                    this->sprite.setTextureRect(this->startRect);


                }

        //Functions

        /*Die Funktionen play und reset werden verwendet um die Animation abzuspielen und zurückzusetzen*/

        void play(const float &deltaTime){
            //update timer
            this->timer += 100.f * deltaTime;
            if(this->timer >= animationTimer){
                //reset timer
                this->timer = 0.f;

                if(this->currentRect != this->endRect){
                    this->currentRect.left += this->width;
                }
                else{ //reset
                    this->currentRect.left = this->startRect.left;
                }

                this->sprite.setTextureRect(this->currentRect);
            }
        }
        void reset(){
            this->timer = 0.f;
            this->currentRect = this->startRect;
        }

    };

    sf::Sprite &sprite;
    sf::Texture &textureSheet;

    std::map<std::string, Animation*> animations;

};


#endif //PROJECT_A_ANIMATIONCOMPONENT_H
