#pragma once

class LevelOne : public Nivele {
    bool exit = false;
public:

    void load() override {
        //AICI IMI SPAWNEZ INAMICI, CAINE, ZIDURI
        nivel = 1;
        backgroundTexture.loadFromFile("sunmapv3.png");
        dog->setPosition({30,350});
        walls.push_back(Wall({0,450},{296,41}));
        walls.push_back(Wall({306,519},{725,51}));
        walls.push_back(Wall({432,310},{372,40}));
        walls.push_back(Wall({1032,239},{185,37}));
        walls.push_back(Wall({1455,370},{185,37}));
        walls.push_back(Wall({1840,534},{185,54}));
        walls.push_back(Wall({2027,463},{185,45}));
        walls.push_back(Wall({2215,365},{185,50}));
        paingivers.push_back(PainGiver({550,272},{130,31}));
        paingivers.push_back(PainGiver({735,485},{206,30}));
        paingivers.push_back(PainGiver({1957,506},{67,30}));
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
        sf::FloatRect win({2293,305},{29,32});
        if (bounds.findIntersection(win))
            return true;
        return false;
    }
    bool getExit() const override {return exit;}

};
