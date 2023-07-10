#include "Player.h"
#include <SFML/Graphics.hpp>



//Constructor
Player::Player(float x, float y, sf::Texture &texture_sheet)
    : jumpCooldown(0.f), playerHealth(5)
{
    this->initVariables();
    this->setPosition(x, y);
    this->setSpriteSize(sprite, 3.5, 3.5);
    this->createMovementComponent(300.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);
    this->animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 0, 7, 0, 144, 80);
    this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 1, 7, 1, 144, 80);
    this->animationComponent->addAnimation("RUN_RIGHT", 10.f, 0, 2, 7, 2, 144, 80);
    this->animationComponent->addAnimation("RUN_LEFT", 10.f, 0, 3, 7, 3, 144, 80);
    this->animationComponent->addAnimation("ATTACK_E_RIGHT", 0.f, 0, 13, 3, 13, 144, 80);
    this->animationComponent->addAnimation("ATTACK_E_LEFT", 0.f, 0, 14, 3, 14, 144, 80);
    this->animationComponent->addAnimation("ATTACK_Q", 10.f, 0, 21, 15, 21, 144, 80);
    this->animationComponent->addAnimation("JUMP", 10.f,0, 10, 2, 10, 144, 80);
    this->animationComponent->addAnimation("DEATH", 10.f,0, 26, 10, 26, 144, 80);
    this->animationComponent->addAnimation("TAKE_HIT", 10.f,0, 25, 3, 25, 144, 80);
    this->animationComponent->addAnimation("PLAYER_DEATH", 10.f,0, 26, 3, 26, 144, 80);


    this->gravity = 15000.8f;
    this->jumpForce = -30000.f;
    this->isJumping = false;

    this->collisionBox.setOutlineColor(sf::Color::Red);
    this->collisionBox.setOutlineThickness(2.f);
    this->collisionBox.setFillColor(sf::Color::Transparent);

    this->getHealth();
    this->pushback();

    this->healthBar.setOutlineColor(sf::Color::Black);
    this->healthBar.setFillColor(sf::Color::Green);
    this->healthBar.setOutlineThickness(1.5f);


    this->damageCoolDown = 1.25f;
    this->attackTimer = 0.0f;
    this->attackCooldown = 0.25f;
    this->attackDamage = 50.f;
}

//Destructor
Player::~Player()
{

}

//Ini Functions
void Player::initVariables()
{

}

void Player::initComponents()
{

}

//Spiel verschiedene Animation je nach Richtung in der die Player läuft/guckt
void Player::update(const float &deltaTime)
{
    this->isDying = false;

    if(!this->playerHealth == 0) {
        this->movementComponent->update(deltaTime);
        this->sprite.move(0, this->gravity * deltaTime);

        if (this->movementComponent->idle()) {
            if (lastMove == -1) {
                this->animationComponent->play("IDLE_LEFT", deltaTime);
            } else if (lastMove == 1) {
                this->animationComponent->play("IDLE_RIGHT", deltaTime);
            }
        } else if (this->movementComponent->movingLeft()) {
            lastMove = -1;
            this->animationComponent->play("RUN_LEFT", deltaTime);
        } else if (this->movementComponent->movingRight()) {
            lastMove = 1;
            this->animationComponent->play("RUN_RIGHT", deltaTime);
        }
        /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            this->animationComponent->play("ATTACK_Q", deltaTime);
        }*/

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            this->animationComponent->play("JUMP", deltaTime);
        }

        if (this->isJumping) {
            this->sprite.move(0, this->gravity * deltaTime);
            this->gravity += 1000.5f; //Anpassen um Gravitationskraft zu ändern
        }


        // Reduce jump cooldown
        if (this->jumpCooldown > 0.f) {
            this->jumpCooldown -= deltaTime;
        }

        if (attackTimer < attackCooldown) {
            attackTimer += deltaTime;
        }

        // Check for jump input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->jumpCooldown <= 0.f) {
            {
                this->isJumping = true;
                this->jumpCooldown = 1.5f; // Set this to the desired cooldown duration in seconds
            }
        }

        //Setzte custom Kollisionbox um den Sprite, da die globalBounds viel zu groß waren
        this->collisionBox.setPosition(this->sprite.getPosition().x + 135.f, this->sprite.getPosition().y + 110.f);
        this->collisionBox.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width - 380.f,
                                                this->sprite.getGlobalBounds().height - 120.f));

        this->healthBar.setPosition(100, 100);
        this->healthBar.setSize(sf::Vector2f(500, 30));

        float currentTime = gameClock.getElapsedTime().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && attackTimer >= attackCooldown) {
            if (lastMove == 1) {
                this->animationComponent->play("ATTACK_E_RIGHT", deltaTime);
                this->createHitbox();
            } else if (lastMove == -1) {
                this->animationComponent->play("ATTACK_E_LEFT", deltaTime);
                this->createHitbox();
            }

            // Setze den Timer zurück
            attackTimer = 0.0f;
        } else {
            this->destroyHitbox();
        }
    }

    else
    {
        if (!this->isDying)
        {
            this->animationComponent->play("PLAYER_DEATH", deltaTime);
            this->isDying = true;
        }
    }

    if (this->isDying && this->animationComponent->isDone("PLAYER_DEATH"))
    {
        this->sprite.setColor(sf::Color::Transparent);
    }
}

void Player::jump()
{
    if (!this->isJumping)
    {
        this->isJumping = false;
        this->gravity = this->jumpForce; // Weise der y-Beschleunigung die Sprungkraft zu
    }
}

sf::Vector2f Player::getPosition() const
{
    return this->sprite.getPosition();
}

void Player::takeDamage(int damage)
{
    playerHealth -= damage;
    if (playerHealth < 0)
    {
        playerHealth = 0;
    }
}

int Player::getHealth()
{
    return playerHealth;
}

void Player::pushback()
{
    this->sprite.move(-60, 0);
}

void Player::updateHealthBar(sf::RectangleShape &healthBar)
{
    healthBar.setSize(sf::Vector2f(this->playerHealth, healthBar.getSize().y));
}

void Player::createHitbox()
{
    this->hitbox.setSize(sf::Vector2f(100.f, 100.f)); // Sie müssen die Größe der Hitbox an Ihr Spiel anpassen
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(sf::Color::Yellow);


    if (lastMove == 1)
    {
        this->hitbox.setPosition(this->sprite.getPosition().x -250 +
        this->sprite.getGlobalBounds().width, this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2);
    }
    else
    {
        this->hitbox.setPosition(this->sprite.getPosition().x + 200 -
            this->hitbox.getSize().x, this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2);
    }
}

void Player::destroyHitbox()
{
    this->hitbox.setSize(sf::Vector2f(0.f, 0.f));
}

void Player::attack(Boss *boss) {
    // Überprüfe, ob die Hitbox des Spielers die des Bosses trifft.
    if (this->hitbox.getGlobalBounds().intersects(boss->collisionBoxBoss.getGlobalBounds())) {
        // Wenn sie sich überschneiden, füge dem Boss Schaden zu.
        boss->takeDamage(this->attackDamage);
    }
}



















