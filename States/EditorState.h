#ifndef PROJECT_A_EDITORSTATE_H
#define PROJECT_A_EDITORSTATE_H
#include "State.h"
#include "../Resource Files/Button.h"


class EditorState : public State {
public:
    EditorState(sf::RenderWindow * window, std::map<std::string, int> * supportedKeys, std::stack<State*> *states);
    virtual ~EditorState();

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


#endif //PROJECT_A_EDITORSTATE_H
