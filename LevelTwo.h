#pragma once

class LevelTwo : public Nivele {
    bool exit = false;
public:

    void load() override {
        //AICI IMI SPAWNEZ INAMICI, CAINE, ZIDURI
        nivel = 2;
        backgroundTexture.loadFromFile("trainmapv2.png");
        dog->setPosition({15,345});
        walls.push_back(Wall({0,413},{300,100}));
        walls.push_back(Wall({301,340},{511,200}));
        walls.push_back(Wall({813,412},{487,104}));
        walls.push_back(Wall({1507,374},{31,48}));
        walls.push_back(Wall({1805,456},{148,60}));
        walls.push_back(Wall({1963,408},{121,40}));
        walls.push_back(Wall({2084,448},{195,64}));
        paingivers.push_back(PainGiver({418,287},{69,34}));
        paingivers.push_back(PainGiver({592,290},{68,24}));
        paingivers.push_back(PainGiver({837,376},{71,28}));
        paingivers.push_back(PainGiver({1119,379},{68,27}));
        paingivers.push_back(PainGiver({1857,423},{68,27}));
    }

    void handleInput(sf::RenderWindow &window) override {
        dog->handleInput(walls);
    }

    void update(float dt) override {
        dog->update(dt,walls,paingivers);
        if (dog->getHealth()==0)gameover = true;
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& wall : walls)
            wall.draw(window);
        for (auto& pain : paingivers)
            pain.draw(window);
        dog->draw(window);
    }

    bool isComplete() const override {
        sf::FloatRect bounds = dog->getBounds();
        sf::FloatRect win({2355,369},{34,34});
        if (bounds.findIntersection(win))
            return true;
        return false;
    }
    bool getExit() const override {return exit;}

};
