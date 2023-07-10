#ifndef PROJECT_A_BOSS_H
#define PROJECT_A_BOSS_H



#include "Entity.h"
//#include "../States/GameState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Player;

class Boss : public Entity{

public:
    Boss(float x, float y, sf::Texture &texture);
    ~Boss();

    void update(Player &player, const float &deltaTime, float currentTime);
    void setPosition(const float x, const float y);
    void attack();

    sf::RectangleShape collisionBoxBoss;
    sf::RectangleShape attackCollisionBox;
    sf::RectangleShape pushBackCollision;

    void hit();
    int attackDamage;
    float attackDuration;
	bool hasDamaged;
    int bossHealth;
    int getBossHealth();
    sf::RectangleShape bossHealthBar;
    sf::Text bossName;

    float xOffset;
    float yOffset = 550.f;
    float attackWidth = 200.f;
    float attackHeight = 250.f;

    void takeDamage(int damage);
    void updateHealthBar(sf::RectangleShape &bossHealthBar);
    bool isDying;

private:
    sf::Vector2f position;
    float speed;

    std::string attackDirection;

    void setBossPosition(float x, float y);

    sf::Vector2f getPosition() const;
};


#endif //PROJECT_A_BOSS_H
