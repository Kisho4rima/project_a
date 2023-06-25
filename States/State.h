#ifndef PROJECT_A_STATE_H
#define PROJECT_A_STATE_H

#include "../Entites/Player.h"

class State {

public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*> *states);
    virtual ~State();

    const bool& getQuit() const;
    void pauseState();
    void unpauseState();

    void endState();
    virtual void updateMousePos();
    virtual void updateInput(const float& deltaTime) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
    std::stack<State*> *states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool paused;

    //track the mouse position
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    //track where the mouse is within the view
    sf::Vector2f mousePosView;

    //Resources
    std::map<std::string, sf::Texture> textures;

    //Functions
    virtual void initKeybinds() = 0;

private:

};


#endif //PROJECT_A_STATE_H
