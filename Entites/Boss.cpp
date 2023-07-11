//Wirklich schwer zu implementieren

#include "Boss.h"
#include "Player.h"
#include <cmath>

Boss::Boss(float x, float y, sf::Texture &texture)
    :position(sf::Vector2f(x, y)), speed(100.f), attackDamage(250.f), bossHealth(500)
{
    this->createAnimationComponent(texture);
    this->setSpriteSize(sprite,5, 5);
    this->setBossPosition(float (x) , float (y));
    this->animationComponent->addAnimation("RUN_LEFT", 10.f, 0, 1, 11, 1, 288, 160);
    this->animationComponent->addAnimation("RUN_RIGHT", 10.f, 0, 2, 11, 2, 288, 160);
    this->animationComponent->addAnimation("ATTACK_LEFT", 10.f, 0, 3, 14, 3, 288, 160);
    this->animationComponent->addAnimation("ATTACK_RIGHT", 10.f, 0, 4, 14, 4, 288, 160);
    this->animationComponent->addAnimation("BOSS_DEATH", 10.f, 0, 5, 21, 5, 288, 160);

    //Vom Boss selber
    this->collisionBoxBoss.setOutlineColor(sf::Color::Red);
    this->collisionBoxBoss.setOutlineThickness(2.f);
    this->collisionBoxBoss.setFillColor(sf::Color::Transparent);

    //Von seiner Attacke
    this->attackCollisionBox.setFillColor(sf::Color::Transparent);
    this->attackCollisionBox.setOutlineColor(sf::Color::Blue);
    this->attackCollisionBox.setOutlineThickness(2.f);

    this->attackDuration = -1;
    this->hasDamaged = false;

    //Boss Lebensanzeige
    this->getBossHealth();
    this->bossHealthBar.setOutlineColor(sf::Color::Black);
    this->bossHealthBar.setFillColor(sf::Color::Red);
    this->bossHealthBar.setOutlineThickness(1.f);

    if (!defeatTheme.openFromFile("../soundtrack/defeatTheme.wav"))
    {
        std::cout << "could not load defeatTheme";
    }
}

Boss::~Boss()
{

}


//Boss bewegt sich zum Sprite hin und Angriffe
void Boss::update(Player &player, const float &deltaTime, float currentTime)
{
    this->isDying = false;

    if (!this->bossHealth == 0) {
        // Get player and boss collision boxes.
        sf::Rect<float> playerCollisionBox = player.collisionBox.getGlobalBounds();
        sf::Rect<float> bossCollisionBox = this->collisionBoxBoss.getGlobalBounds();

        //Attackrange
        float attackRange = 430.f;

        sf::Vector2f futureBossCollisionBox = this->sprite.getPosition();

        // If the boss is to the left of the player, move right.
        if (bossCollisionBox.left < playerCollisionBox.left) {
            futureBossCollisionBox.x += this->speed * deltaTime;
        }

            // If the boss is to the right of the player, move left.
        else if (bossCollisionBox.left > playerCollisionBox.left) {
            futureBossCollisionBox.x -= this->speed * deltaTime;
        }

        float distanceToPlayer = std::abs(bossCollisionBox.left - playerCollisionBox.left);

        // Check ob der Player in range ist und der Boss nicht schon angreift
        if (distanceToPlayer <= attackRange && this->attackDuration == -1) {
            //std::cout << "Boss is in attack mode!" << std::endl;

            this->attackDuration = 0;
            //If the boss is to the left of the player, attack right.
            if (bossCollisionBox.left < playerCollisionBox.left) {
                this->animationComponent->play("ATTACK_RIGHT", deltaTime);
                this->attackDirection = "right";
                //std::cout << "Boss ist links vom player";
            }
                // If the boss is to the right of the player, attack left.
            else {
                this->animationComponent->play("ATTACK_LEFT", deltaTime);
                this->attackDirection = "left";
                //std::cout << "Boss ist rechts vom player";
            }
            float xOffset = this->attackDirection == "right" ? 1050 : 190;
            this->attackCollisionBox.setPosition(this->sprite.getPosition().x + xOffset - 100,
                                                 this->sprite.getPosition().y + this->yOffset);
            this->attackCollisionBox.setSize(sf::Vector2f(attackWidth + 120, attackHeight));
        } else if (this->attackDuration == -1) {
            this->sprite.setPosition(futureBossCollisionBox.x, this->sprite.getPosition().y);
            this->collisionBoxBoss.setPosition(futureBossCollisionBox.x + 552.f, this->sprite.getPosition().y + 280.f);
            if (bossCollisionBox.left < playerCollisionBox.left) {
                this->animationComponent->play("RUN_RIGHT", deltaTime);
            } else {
                this->animationComponent->play("RUN_LEFT", deltaTime);
            }
        } else {
            this->animationComponent->play(this->attackDirection == "right" ? "ATTACK_RIGHT" : "ATTACK_LEFT",
                                           deltaTime);
            this->attackDuration += deltaTime;
        }

        // CollisionBox Position update damit er mit dem Sprite übereinstimmt
        this->collisionBoxBoss.setPosition(this->sprite.getPosition().x + 552.f, this->sprite.getPosition().y + 280.f);
        this->collisionBoxBoss.setSize(
                sf::Vector2f(this->sprite.getGlobalBounds().width - 1150.f,
                             this->sprite.getGlobalBounds().height - 290.f));

        //Pushback KollisionBox, falls der sprite mit dem Boss Kollidiert wird er geknockbackt
        this->pushBackCollision.setFillColor(sf::Color::Transparent);
        this->pushBackCollision.setOutlineThickness(2.f);
        this->pushBackCollision.setOutlineColor(sf::Color::Cyan);
        this->pushBackCollision.setSize(sf::Vector2f(attackWidth + 100, attackHeight / 1.f));
        this->pushBackCollision.setPosition(this->sprite.getPosition().x + 550, this->sprite.getPosition().y + 550);

        if (this->pushBackCollision.getGlobalBounds().intersects(player.collisionBox.getGlobalBounds())) {
            float pushBackDistance = 70.0f;
            float boss_x = this->pushBackCollision.getGlobalBounds().left;
            if (player.getPosition().x < boss_x) {
                // Spieler steht links vom Boss, stoße den Spieler nach links zurück
                player.setPosition(player.getPosition().x - pushBackDistance, player.getPosition().y);
            } else {
                // Spieler steht rechts vom Boss, stoße den Spieler nach rechts zurück
                player.setPosition(player.getPosition().x + pushBackDistance, player.getPosition().y);
            }
        }

        if (this->attackDuration > 1 && !this->hasDamaged) {
            if (this->attackCollisionBox.getGlobalBounds().intersects(player.collisionBox.getGlobalBounds())) {
                player.takeDamage(this->attackDamage);
                this->hasDamaged = true;
            }
        }

        if (this->animationComponent->isDone(this->attackDirection == "right" ? "ATTACK_RIGHT" : "ATTACK_LEFT")) {
            this->attackCollisionBox.setSize(sf::Vector2f(0.f, 0.f));
            this->attackDuration = -1;
            this->hasDamaged = false;
        }
    }
    else
    {
        if (!this->isDying)
        {
            this->animationComponent->play("BOSS_DEATH", deltaTime);
            this->isDying = true;
        }
    }

    if (this->isDying && this->animationComponent->isDone("BOSS_DEATH"))
    {
        this->sprite.setColor(sf::Color::Transparent);
    }

    this->bossHealthBar.setPosition(2250, 100);
    this->bossHealthBar.setSize(sf::Vector2f(500, 30));
}


//Legt Position auf dem Screen Fest
void Boss::setBossPosition(float x, float y)
{
    this->sprite.setPosition(700, 750);
    //std::cout << "Boss position: " << this->getPosition().x << ", " << this->getPosition().y << std::endl;
}

void Boss::setPosition(const float x, const float y)
{
    this->position.x = x;
    this->position.y = y;
    this->sprite.setPosition(x, y);
}

sf::Vector2f Boss::getPosition() const
{
    return this->position;
}

int Boss::getBossHealth()
{
    return bossHealth;
}

void Boss::takeDamage(int damage)
{
    this->bossHealth -= damage;
    std::cout << "Boos took damage";

    if (this->bossHealth <= 0)
    {
        this->bossHealth = 0;
    }

}

void Boss::updateHealthBar(sf::RectangleShape &bossHealthBar)
{
    bossHealthBar.setSize(sf::Vector2f(this->bossHealth, bossHealthBar.getSize().y));
}

void Boss::playDefeatTheme()
{
    defeatTheme.play();
}







