#ifndef LEVEL_THREE_H
#define LEVEL_THREE_H

#include "Wall.h"

class LevelThree : public Nivele {
    bool exit = false;
public:

    void load() override {
        //AICI IMI SPAWNEZ INAMICI, CAINE, ZIDURI
        nivel = 3;
        backgroundTexture.loadFromFile("sunmap.png");
        dog->setPosition({200,200});
        walls.push_back(Wall({0,532},{800,100}));
        walls.push_back(Wall({206,142},{122,38}));
        walls.push_back(Wall({475,325},{122,38}));
        walls.push_back(Wall({648,198},{122,38}));
    }

    void handleInput(sf::RenderWindow &window) override {
        dog->handleInput(walls);
    }

    void update(float dt) override {
        dog->update(dt,walls);
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& wall : walls)
            wall.draw(window);
        dog->draw(window);
    }

    bool isComplete() const override {
        return dog->getPosition().x > 700 && dog->getPosition().y < 100;
    }
    bool getExit() const override {return exit;}

};
#endif // LEVEL_THREE_H