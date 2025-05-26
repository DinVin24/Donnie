#pragma once
#include <SFML/Graphics.hpp>
#include "Dog.h"
#include "HealthObserver.h"
#include <iostream>

class HealthDisplay : public HealthObserver {
    sf::Sprite heart;
    int currentHealth = 3;

public:
    HealthDisplay(const sf::Texture& texture)
    : heart(texture){
        heart.setScale(sf::Vector2f(1, 1));
    }

    void onHealthChange(int newHealth) override {
        this->currentHealth = newHealth;
    }

    void draw(sf::RenderWindow& window, const sf::View& view) {
        for (int i=0; i < currentHealth; ++i) {
            heart.setPosition({view.getCenter().x + 332 - i * (heart.getGlobalBounds().size.x + 5), 30.f});
            window.draw(heart);
        }
    }

};