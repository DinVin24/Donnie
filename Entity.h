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

    virtual void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    virtual ~Entity() = default;
};

#endif
