//Wirklich schwer zu implementieren

#include "Boss.h"
#include <cmath>

Boss::Boss(float x, float y, sf::Texture &texture)
    :position(sf::Vector2f(x, y)), speed(100.f), isAttacking(false), attackDamage(1.f)
{
    this->createAnimationComponent(texture);
    this->setSpriteSize(sprite,5, 5);
    this->setBossPosition(float (x) , float (y));
    this->animationComponent->addAnimation("RUN_LEFT", 10.f, 0, 1, 11, 1, 288, 160);
    this->animationComponent->addAnimation("RUN_RIGHT", 10.f, 0, 2, 11, 2, 288, 160);
    this->animationComponent->addAnimation("ATTACK_LEFT", 10.f, 0, 3, 14, 3, 288, 160);
    this->animationComponent->addAnimation("ATTACK_RIGHT", 10.f, 0, 4, 14, 4, 288, 160);

    //Vom Boss selber
    this->collisionBoxBoss.setOutlineColor(sf::Color::Red);
    this->collisionBoxBoss.setOutlineThickness(2.f);
    this->collisionBoxBoss.setFillColor(sf::Color::Transparent);

    //Von seiner Attacke
    this->attackCollisionBox.setFillColor(sf::Color::Transparent);
    this->attackCollisionBox.setOutlineColor(sf::Color::Blue);
    this->attackCollisionBox.setOutlineThickness(2.f);

    this->attackCooldown = 0.f;
    this->attackCooldownTimer = 0.f;
    this->canAttack = true;
    this->attackTimer = 0.f;
    this->attackDelay = 2.f; //Schaden alle 2 sek
}

Boss::~Boss()
{

}


//Boss bewegt sich zum Sprite hin und Angriffe
void Boss::update(Player &player, const float &deltaTime)
{
    // Get player and boss collision boxes.
    sf::Rect<float> playerCollisionBox = player.collisionBox.getGlobalBounds();
    sf::Rect<float> bossCollisionBox = this->collisionBoxBoss.getGlobalBounds();

    //Attackrange
    float attackRange = 430.f;

    sf::Vector2f futureBossCollisionBox = this->sprite.getPosition();

    // If the boss is to the left of the player, move right.
    if (bossCollisionBox.left < playerCollisionBox.left)
    {
        futureBossCollisionBox.x += this->speed * deltaTime;
    }

        // If the boss is to the right of the player, move left.
    else if (bossCollisionBox.left > playerCollisionBox.left)
    {
        futureBossCollisionBox.x -= this->speed * deltaTime;
    }

    float distanceToPlayer = std::abs(bossCollisionBox.left - playerCollisionBox.left);

    // Check ob der Player in range ist und der Boss nicht schon angreift
    if (distanceToPlayer <= attackRange && !this->isAttacking && this->canAttack)
    {
        //std::cout << "Boss is in attack mode!" << std::endl;

        //If the boss is to the left of the player, attack right.
        if (bossCollisionBox.left < playerCollisionBox.left)
        {
            this->animationComponent->play("ATTACK_RIGHT", deltaTime);
            this->isAttacking = true;
            this->attackDirection = "right";
            //std::cout << "Boss ist links vom player";
        }
        // If the boss is to the right of the player, attack left.
        else
        {
            this->animationComponent->play("ATTACK_LEFT", deltaTime);
            this->isAttacking = true;
            this->attackDirection = "left";
            //std::cout << "Boss ist rechts vom player";
        }
    }

    else if (!this->isAttacking)
    {
        this->sprite.setPosition(futureBossCollisionBox.x, this->sprite.getPosition().y);
        this->collisionBoxBoss.setPosition(futureBossCollisionBox.x +552.f, this->sprite.getPosition().y + 280.f);
        if (bossCollisionBox.left < playerCollisionBox.left)
        {
            this->animationComponent->play("RUN_RIGHT", deltaTime);
        }
        else
        {
            this->animationComponent->play("RUN_LEFT", deltaTime);
        }
    }

    //Attack Hitbox und dass der Spieler schaden kriegt, wenn er in der Hitbox drinnen ist.
    /*if (this->isAttacking && this->canAttack)
    {
        this->canAttack = false;

        //Wenn die Animation läuft, mach weiter und ignoriere die Position des Spielers
        this->animationComponent->play(this->attackDirection == "right" ? "ATTACK_RIGHT" : "ATTACK_LEFT", deltaTime);

        if (this->attackDirection == "right") {
            xOffset = 1050.f;
        } else {
            xOffset = 190.f;
        }

        //Größe der Collisionbox relativ zum Boss
        this->attackCollisionBox.setPosition(this->sprite.getPosition().x + xOffset,
                                             this->sprite.getPosition().y + yOffset);

        std::cout << "AttackCollisionBox position: " << this->attackCollisionBox.getPosition().x << ", "
                  << this->attackCollisionBox.getPosition().y << std::endl;

        //Größe der Collisionbox
        this->attackCollisionBox.setSize(sf::Vector2f(attackWidth, attackHeight));

        // Wenn die Animation fast beendet ist, verursache Schaden
        if (this->animationComponent->isDone(this->attackDirection == "right" ? "ATTACK_RIGHT" : "ATTACK_LEFT"))
        {
            //std::cout << "Attack animation is done!" << std::endl;

            if (this->attackCollisionBox.getGlobalBounds().intersects(player.collisionBox.getGlobalBounds()))
            {
                if (this->attackTimer >= this->attackDelay)
                {
                    player.takeDamage(this->attackDamage);
                    this->attackTimer = 0.f;
                }
                else
                {
                    this->attackTimer += deltaTime;
                }
            }
            // Nachdem der Schaden verursacht wurde, setze isAttacking zurück auf false
            this->isAttacking = false;
        }
    }
    else
    {
        //Wenn der boss keine Attacke macht, existiert diese CollisionBox nicht
        this->attackCollisionBox.setSize(sf::Vector2f(0.f, 0.f));
    }*/



    // CollisionBox Position update damit er mit dem Sprite übereinstimmt
    this->collisionBoxBoss.setPosition(this->sprite.getPosition().x + 552.f, this->sprite.getPosition().y + 280.f);
    this->collisionBoxBoss.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width - 1150.f, this->sprite.getGlobalBounds().height - 290.f));

    //Pushback KollisionBox, falls der sprite mit dem Boss Kollidiert wird er geknockbackt
    this->pushBackCollision.setFillColor(sf::Color::Transparent);
    this->pushBackCollision.setOutlineThickness(2.f);
    this->pushBackCollision.setOutlineColor(sf::Color::Cyan);
    this->pushBackCollision.setSize(sf::Vector2f(attackWidth + 100, attackHeight / 1.f));
    this->pushBackCollision.setPosition(this->sprite.getPosition().x +550, this->sprite.getPosition().y + 550);

    if (this->pushBackCollision.getGlobalBounds().intersects(player.collisionBox.getGlobalBounds()))
    {
        float pushBackDistance = 50.0f;

        if (player.getPosition().x < this->getPosition().x)
        {
            // Spieler steht links vom Boss, stoße den Spieler nach links zurück
            player.setPosition(player.getPosition().x - pushBackDistance, player.getPosition().y);
        }
        else
        {
            // Spieler steht rechts vom Boss, stoße den Spieler nach rechts zurück
            player.setPosition(player.getPosition().x + pushBackDistance, player.getPosition().y);
        }
    }

    if (this->attackCooldownTimer >= this->attackCooldown)
    {
        //std::cout << "Attack cooldown is over!" << std::endl;
        this->attackCooldownTimer = 0.f;
        this->canAttack = true;
        //std::cout << "canAttack: " << canAttack;
    }
    else
    {
        this->attackCooldownTimer += deltaTime;
    }

    if (this->isAttacking && this->attackCollisionBox.getGlobalBounds().intersects(player.collisionBox.getGlobalBounds()))
    {
        this->attackTimer += deltaTime;

        if (this->attackTimer >= this->attackDelay)
        {
            player.takeDamage(this->attackDamage);
            this->attackTimer = 0.0f;
        }
        if (this->animationComponent->isDone(this->attackDirection == "right" ? "ATTACK_RIGHT" : "ATTACK_LEFT"))
        {
            this->isAttacking = false;
            this->attackCollisionBox.setSize(sf::Vector2f(0.f, 0.f));
        }
    }
    else
    {
        // Wenn der Boss nicht angreift, setzen Sie die Größe der Angriffskollisionsbox auf 0.
        this->attackCollisionBox.setSize(sf::Vector2f(0.f, 0.f));
    }


    if (this->isAttacking && this->canAttack) {
        this->canAttack = false;

        this->animationComponent->play(this->attackDirection == "right" ? "ATTACK_RIGHT" : "ATTACK_LEFT", deltaTime);

        // Positioniere die attackCollisionBox basierend auf xOffset und yOffset.
        if (this->attackDirection == "right") {
            xOffset = 1050.f;
        } else {
            xOffset = 190.f;
        }
        this->attackCollisionBox.setPosition(this->sprite.getPosition().x + xOffset, this->sprite.getPosition().y + yOffset);
        this->attackCollisionBox.setSize(sf::Vector2f(attackWidth, attackHeight));

        // Wenn die Animation fertig ist, bereiten Sie sich darauf vor, in der nächsten Frame Schaden zu verursachen
        if (this->animationComponent->isDone(this->attackDirection == "right" ? "ATTACK_RIGHT" : "ATTACK_LEFT")) {
            this->isAttacking = false;
            this->readyToDamage = true;
        }
    } else if (this->readyToDamage) {
        // Wenn wir bereit sind, Schaden zu verursachen und der Spieler in der attackCollisionBox ist, verursachen Sie Schaden
        if (this->attackCollisionBox.getGlobalBounds().intersects(player.collisionBox.getGlobalBounds())) {
            player.takeDamage(this->attackDamage);
        }
        this->readyToDamage = false;

        // Setze die Größe der attackCollisionBox auf 0
        this->attackCollisionBox.setSize(sf::Vector2f(0.f, 0.f));
    } else {
        // Setze die Größe der attackCollisionBox auf 0, wenn der Boss nicht angreift.
        this->attackCollisionBox.setSize(sf::Vector2f(0.f, 0.f));
    }
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

void Boss::attack()
{

}







