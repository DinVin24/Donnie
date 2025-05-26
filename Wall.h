#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Wall {
protected:
    sf::RectangleShape shape;

public:
    Wall(sf::Vector2f position, sf::Vector2f size) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Transparent);
    }

    virtual ~Wall() = default;

    virtual void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    friend std::ostream& operator<<(std::ostream& os, const Wall& obj) {
        os << "POZ: " << obj.getPosition().x << ' ' << obj.getPosition().y << "\n\n";
        return os;
    }


};
