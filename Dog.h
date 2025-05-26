#pragma once

#include "Entity.h"
#include "Wall.h"
#include "PainGiver.h"
#include "GameException.h"
#include "HealthObserver.h"
#include <vector>
#include <algorithm>

class Dog : public Entity {
private:
    //movement
    sf::Vector2f velocity; //viteza in timp real a cainelui pe ambele axe
    sf::Time momentum; //cat timp stau in aer pana incep sa cad
    float speed = 6.f; //viteza cu care se misca cand apasam pe un buton
    float jumpHeight = 10.f;//viteza cu care sare
    float fallSpeed = 10.f; //viteza cu care cade
    struct dir{
        int x=0,y=1;
    }direction;
    struct  {
        bool stanga=true,
        dreapta=true;
    }am_voie;//TRUE DACA MA POT MISCA IN ST/DR
    bool iAmRunning = false;

    //animatii
    sf::Texture walk1,walk2,walk3,walk4,walk5,walk6;
    sf::Texture jump1,jump2,jump3;
    sf::Texture defaultStance;
    int frame = 0;

    //viata
    int health = 3;
    int invincibility = 0;
    std::vector<HealthObserver*> observers;

public:
    Dog(const sf::Texture& texture, sf::Vector2f position)
        : Entity(texture, position) {
        if (!walk1.loadFromFile("walking1.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("walking1.png");
        if (!walk2.loadFromFile("walking2.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("walking2.png");
        if (!walk3.loadFromFile("walking3.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("walking3.png");
        if (!walk4.loadFromFile("walking4.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("walking4.png");
        if (!walk5.loadFromFile("walking5.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("walking5.png");
        if (!walk6.loadFromFile("walking6.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("walking6.png");
        if (!jump1.loadFromFile("jump1.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("jump1.png");
        if (!jump2.loadFromFile("jump2.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("jump2.png");
        if (!jump3.loadFromFile("jump3.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("jump3.png");
        if (!defaultStance.loadFromFile("defaultStance.png",false, sf::IntRect({0, 0}, {100, 100})))
            throw AssetLoadException("defaultStance.png");
    }

    void handleInput(const std::vector<Wall>& walls);
    bool onGround(const std::vector<Wall>& walls);
    void update(float deltaTime, const std::vector<Wall>& walls, const std::vector<PainGiver>& paingivers);

    void draw(sf::RenderWindow& window){
        window.draw(sprite);
    }
    void fall(const std::vector<Wall>& walls);
    void checkCollisions(const std::vector<Wall>& walls);
    void checkDamage(const std::vector<PainGiver>& paingivers);
    void setVelocity(const sf::Vector2f& v) {velocity = v;}
    sf::Vector2f getVelocity() const {return velocity;}

    dir getDirection() {return direction;}
    void setDirection(int x,int y){direction.x = x; direction.y = y;}
    void animateMovement();
    int getInvincibility() const {return invincibility;}
    int getHealth() const {return health;}
    void setHealth(int newHealth) {
        health = newHealth;
        for (auto obs : observers) {
            obs->onHealthChange(health);
        }

    }
    void addObserver(HealthObserver* obs) {
        observers.push_back(obs);
    }
    void removeObserver(HealthObserver* obs) {
        observers.erase(std::remove(observers.begin(),
            observers.end(), obs), observers.end());
    }

    friend std::ostream& operator<<(std::ostream& os, const Dog& d) {

        os << "VIATA: " << d.getHealth() << '\n';
        os << "INVINCIBILITY: " << d.getInvincibility() << '\n';
        os << "POZ: " << d.getPosition().x << ' ' << d.getPosition().y << '\n';
        os << "VITEZA: " << d.getVelocity().x << '\n';
        os << "SALT: " << d.getVelocity().y;
        os << "\n\n";
        return os;
    }


};