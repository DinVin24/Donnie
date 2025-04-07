#ifndef DOG_HPP
#define DOG_HPP
#include "Entity.h"
class Dog : public Entity {
private:
    sf::Vector2f velocity;
    struct dir{
        int x=0,y=0;
    }direction;
    bool onGround = false;
    sf::Time momentum;

public:
    Dog(const sf::Texture& texture, sf::Vector2f position)
        : Entity(texture, position) {}

    void handleInput();

    void update(float deltaTime) {
        sprite.move(velocity * deltaTime);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
    void fall();
    void setVelocity(const sf::Vector2f& v) {velocity = v;}
    sf::Vector2f getVelocity() {return velocity;}

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();//marginile ca sa fac o intersectie
    }
    dir getDirection() {return direction;}
    void setDirection(int x,int y){direction.x = x; direction.y = y;}
    bool getOnGround() {return onGround;}
    void setOnGround(bool b) {onGround = b;}
};
#endif