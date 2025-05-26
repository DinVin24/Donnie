#pragma once

#include "Nivele.h"
class TestLevel : public Nivele {
    bool exit = false;
public:

    void load() override {
        //AICI IMI SPAWNEZ INAMICI, CAINE, ZIDURI
        nivel = 0;
        backgroundTexture.loadFromFile("leopard.jpg");
        dog->setPosition({200,200});
        walls.push_back(Wall({0,600},{1600,100}));
        walls.push_back(Wall({500,500},{100,100}));
        paingivers.push_back(PainGiver({400,300},{50,50}));
        paingivers.push_back(PainGiver({700,550},{100,100}));

    }

    void handleInput(sf::RenderWindow &window) override {
        dog->handleInput(walls);
    }

    void update(float dt) override {
        dog->update(dt,walls,paingivers);
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& wall : walls)
            wall.draw(window);
        for (auto& pain : paingivers)
            pain.draw(window);
        dog->draw(window);
    }

    bool isComplete() const override {
        return dog->getPosition().x > 800;
    }
    bool getExit() const override {return exit;}

};