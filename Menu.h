#pragma once

class Menu : public Nivele {
    bool exit=false,start=false;
public:

    void load() override {
        nivel = -1;
        if (!backgroundTexture.loadFromFile("menu.png"))
            throw AssetLoadException("menu.png");
        dog->setPosition({400, 300});
        walls.push_back(Wall({0, 600}, {800, 2}));
        walls.push_back(Wall({-4,0},{4,600}));
        walls.push_back(Wall({800,0},{4,600}));
    }

    void handleInput(sf::RenderWindow& window) override {
        sf::IntRect s ({321,312},{170,81}); //pozitia butonului de start
        sf::IntRect e ({350,430},{108,67}); //pozitia butonului de exit
        sf::IntRect instr ({51,501},{72,78}); //pozitia butonului de instructiuni
        dog->handleInput(walls);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            sf::Vector2i poz = sf::Mouse::getPosition(window);
            if (e.contains(poz)) exit = true;
            if (s.contains(poz)) start = true;
            if (instr.contains(poz)) {
                nivel = 100;
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
