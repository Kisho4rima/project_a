#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color){

    this->buttonState = BTN_IDLE;
    this->bShape.setPosition(sf::Vector2(x, y));
    this->bShape.setSize(sf::Vector2f(width, height));
    this->bShape.setFillColor(idle_color);
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);

    this->text.setPosition(
            this->bShape.getPosition().x + (this->bShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            this->bShape.getPosition().y + (this->bShape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = active_color;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;
}

Button::~Button() = default;

//Functions

void Button::render(sf::RenderTarget *target) {

    target->draw(this->bShape);
    target->draw(text);

}

void Button::update(const sf::Vector2f &mousePos) {

    //Updated den boolean Wert für wenn man über den button hovert und pressed

    //Idle
    this->buttonState = BTN_IDLE;
    //Hover
    if(this->bShape.getGlobalBounds().contains(mousePos)){

        this->buttonState = BTN_HOVER;
        //Pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState){
        case BTN_IDLE:
            this->bShape.setFillColor(this->idleColor);
            this->text.setFillColor(this->textIdleColor);
            break;

        case BTN_HOVER:
            this->bShape.setFillColor(this->hoverColor);
            this->text.setFillColor(this->textHoverColor);

            break;

        case BTN_ACTIVE:
            this->bShape.setFillColor(this->activeColor);
            this->text.setFillColor(this->textActiveColor);

            break;

        default:
            this->bShape.setFillColor(sf::Color::Blue);
            this->text.setFillColor(sf::Color::Red);
            break;
        
    }

}

const bool Button::isPressed() const {

    if(this->buttonState == BTN_ACTIVE){
        return true;
    }
    return false;
}
