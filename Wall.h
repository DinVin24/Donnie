#ifndef WALL_HPP
#define WALL_HPP

#include <SFML/Graphics.hpp>

class Wall {
private:
    sf::RectangleShape shape;  // Wall represented as a rectangle

public:
    Wall(sf::Vector2f position, sf::Vector2f size) {
        shape.setSize(size);          // Set size of the wall
        shape.setPosition(position);  // Set position of the wall
        shape.setFillColor(sf::Color::Red);  // You can change the color
    }

    // Draw the wall
    void draw(sf::RenderWindow& window) {
        window.draw(shape);  // Render the wall on screen
    }

    // Get the bounds of the wall for collision detection
    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();  // Return bounding box of the wall
    }
    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }
};

#endif
