#ifndef DOG_HPP
#define DOG_HPP
#include "Entity.h"
#include "Wall.h"
class Dog : public Entity {
private:
    sf::Vector2f velocity;
    float speed = 200.f;
    struct dir{
        int x=0,y=1;
    }direction;
    struct  {
        bool stanga=true,dreapta=true;//TRUE DACA MA POT MISCA IN ST/DR
    }am_voie;
    sf::Time momentum;

public:
    Dog(const sf::Texture& texture, sf::Vector2f position)
        : Entity(texture, position) {}

    void handleInput(const std::vector<Wall>& walls);
    bool onGround(const std::vector<Wall>& walls);
    void update(float deltaTime, const std::vector<Wall>& walls);

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
    void fall(const std::vector<Wall>& walls);
    void checkCollisions(const std::vector<Wall>& walls);
    void setVelocity(const sf::Vector2f& v) {velocity = v;}
    sf::Vector2f getVelocity() {return velocity;}

    dir getDirection() {return direction;}
    void setDirection(int x,int y){direction.x = x; direction.y = y;}


};
#endif