#include <SFML/Graphics.hpp>
class Menu : public Nivele {
public:

    void load() override {
        backgroundTexture.loadFromFile("menu.jpg");
        dog->setPosition({400, 300});
        walls.push_back(Wall({0, 600}, {800, 2}));
        walls.push_back(Wall({-4,0},{4,600}));
        walls.push_back(Wall({800,0},{4,600}));
    }

    void handleInput() override {
        dog->handleInput(walls);
    }

    void update(float dt) override {
        dog->update(dt, walls);
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& wall : walls)
            wall.draw(window);
        dog->draw(window);
    }

    bool isComplete() const override {
        return dog->getPosition().x > 800;
    }
    sf::Texture& getBackground(){return this->backgroundTexture;}
};