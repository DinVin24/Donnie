#pragma once

class VictoryScreen : public Nivele {
    bool exit=false,start=false;
public:

    void load() override {
        nivel = 9;
        if (!backgroundTexture.loadFromFile("youwon.jpg"))
            throw AssetLoadException("youwon.jpg");
        dog->setPosition({0, 700});
        walls.push_back(Wall({0, 599}, {800, 2}));
    }

    void handleInput(sf::RenderWindow& window) override {
        // sf::IntRect s ({321,312},{170,81});
        sf::IntRect e ({344,442},{135,63}); //pozitia butonului de exit
        dog->handleInput(walls);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            sf::Vector2i poz = sf::Mouse::getPosition(window);
            if (e.contains(poz)) exit = true;
            // if (s.contains(poz)) start = true;
        }
    }

    void update(float dt) override {
        dog->update(dt, walls,paingivers);
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& wall : walls)
            wall.draw(window);
        for (auto& pain : paingivers)
            pain.draw(window);
        dog->draw(window);
    }

    bool isComplete() const override {
        return start;
    }
    bool getExit() const override {
        return exit;
    }
    sf::Texture& getBackground(){return this->backgroundTexture;}
};
