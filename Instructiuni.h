#pragma once

class Instructiuni : public Nivele {
    bool exit=false,start=false;
public:

    void load() override {
        nivel = 101;
        if (!backgroundTexture.loadFromFile("instructiuni.png"))
            throw AssetLoadException("instructiuni.png");
        dog->setPosition({400, 300});
        walls.push_back(Wall({0, 600}, {800, 2}));
        walls.push_back(Wall({-4,0},{4,600}));
        walls.push_back(Wall({800,0},{4,600}));
    }

    void handleInput(sf::RenderWindow& window) override {
        sf::IntRect b ({19,506},{126,72}); //pozitia butonului back
        dog->handleInput(walls);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            sf::Vector2i poz = sf::Mouse::getPosition(window);
            if (b.contains(poz)) {
                start = true;
                sf::sleep(sf::milliseconds(100));
            }
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
