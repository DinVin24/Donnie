// #include "Nivele.h"
// #include "SFML/Graphics.hpp"
// class TestLevel : public Nivele {
//     sf::RenderWindow window;
//     sf::Texture texture,dogtexture;
// public:
//     TestLevel :: TestLevel() {
//         window.setFramerateLimit(60);
//         window.setSize({800,600});
//         window.setTitle("Donnie the Doggie");
//         texture.loadFromFile("hole.jpg");
//         texture.resize({1200,600},{false});
//
//         sf::Texture donnie_image("donsprite.png", false, sf::IntRect({0, 0}, {87, 51}));
//         sf::Sprite sprite(texture);
//
//         sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));//ASTA-I PT SCROLLING VIEW
//         window.setView(view);
//
//
//         Dog donnie(donnie_image,{100.f,300.f});
//         sf::Clock clock;
//         std::vector<Wall> walls;
//         walls.push_back(Wall(sf::Vector2f(300, 400), sf::Vector2f(50, 200)));
//         walls.push_back(Wall(sf::Vector2f(500, 300), sf::Vector2f(50, 150)));
//         walls.push_back(Wall(sf::Vector2f(0,550),sf::Vector2f(2000,50)));
//     }
//     // void  set_values() {
//     //     dogtexture
//     //
//     //
//     // }
//
// };
#include "Nivele.h"
class TestLevel : public Nivele {
    bool exit = false;
public:

    void load() override {
        //AICI IMI SPAWNEZ INAMICI, CAINE, ZIDURI
        backgroundTexture.loadFromFile("hole.jpg");
        dog->setPosition({200,200});
        walls.push_back(Wall({0,600},{1600,100}));
        walls.push_back(Wall({500,500},{100,50}));
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
        return dog->getPosition().x > 800;
    }
    bool getExit() const override {return exit;}

};