#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Sprite sprite;
    sf::Vector2f velocity;

public:
    Entity(const sf::Texture& texture, sf::Vector2f position)
        : sprite(texture) {
        sprite.setPosition(position);
    }

    virtual void handleInput() {}
    virtual void update(float deltaTime) {
        sprite.move(velocity * deltaTime);
    }
    virtual void fall(){}
    void setTexture(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }
    sf::Texture getTexture(){return sprite.getTexture();}
    virtual void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
    void flipSprite(float x) {
        sprite.setScale({x,1.f});
    }
    void setPosition(sf::Vector2f position) {
        sprite.setPosition(position);
    }
    sf::Vector2f getPosition() const {return sprite.getPosition();}
    void move(sf::Vector2f direction) {
        sprite.move(direction);
    }
    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();//marginile ca sa fac o intersectie
    }
    virtual ~Entity() = default;
};

#endif
