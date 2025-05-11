#ifndef DOG_HPP
#define DOG_HPP
#include "Entity.h"
#include "GameException.h"
#include "Wall.h"
#include "PainGiver.h"
class Dog : public Entity {
private:
    sf::Texture walk1,walk2,walk3,walk4,walk5,walk6;
    sf::Texture jump1,jump2,jump3;
    sf::Texture defaultStance;
    bool iAmRunning = false;
    sf::Vector2f velocity;
    float speed = 6.f;// 300.f
    float jumpHeight = 10.f; //500.f
    float fallSpeed = 10.f; //500.f
    struct dir{
        int x=0,y=1;
    }direction;
    struct  {
        bool stanga=true,dreapta=true;//TRUE DACA MA POT MISCA IN ST/DR
    }am_voie;
    sf::Time momentum;
    int frame = 0;
    int health = 3;
    int invincibility = 0;

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
        defaultStance.loadFromFile("defaultStance.png",false, sf::IntRect({0, 0}, {100, 100}));
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
    sf::Vector2f getVelocity() {return velocity;}

    dir getDirection() {return direction;}
    void setDirection(int x,int y){direction.x = x; direction.y = y;}
    void animateMovement();
    int getHealth(){return health;}
    void setHealth(int health){this->health = health;}



};
#endif