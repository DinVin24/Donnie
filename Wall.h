#ifndef WALL_HPP
#define WALL_HPP

#include <SFML/Graphics.hpp>

class Wall {
private:
    sf::RectangleShape shape;

public:
    Wall(sf::Vector2f position, sf::Vector2f size) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);  //SCHIMBA MAI TARZIU INTR-O TEXTURA PLS
    }

    // Draw the wall
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }
};

#endif
