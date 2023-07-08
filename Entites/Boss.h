#ifndef PROJECT_A_BOSS_H
#define PROJECT_A_BOSS_H


#include "Player.h"
#include "Entity.h"
//#include "../States/GameState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Boss : public Entity{

public:
    Boss(float x, float y, sf::Texture &texture);
    ~Boss();

    void update(Player &player, const float &deltaTime);
    void setPosition(const float x, const float y);
    void attack();

    sf::RectangleShape collisionBoxBoss;
    sf::RectangleShape attackCollisionBox;
    sf::RectangleShape pushBackCollision;

    void hit();
    int attackDamage;
    float attackTimer;
    float attackDelay;

    float xOffset;
    float yOffset = 550.f;
    float attackWidth = 200.f;
    float attackHeight = 250.f;

    //Wegamachen
    bool readyToDamage = false;


private:
    sf::Vector2f position;
    float speed;

    int bossHealth;
    std::string attackDirection;

    void setBossPosition(float x, float y);

    bool isAttacking;
    float attackCooldown;
    float attackCooldownTimer;
    bool canAttack;


    sf::Vector2f getPosition() const;
};


#endif //PROJECT_A_BOSS_H