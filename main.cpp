#include "Functii.cpp"
#include <SFML/Graphics.hpp>
#include <memory>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Donnie the Doggie");
    window.setFramerateLimit(60);
    sf::Texture texture("hole.jpg", false, sf::IntRect({0, 0}, {1200, 600})); // Throws sf::Exception if an error occurs
    sf::Sprite backgroundSprite(texture);

    sf::Texture donnie_image("donsprite.png", false, sf::IntRect({0, 0}, {87, 51}));

    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));
    window.setView(view);

    sf::Clock clock;

    std::unique_ptr<TestLevel> currentLevel = std::make_unique<TestLevel>(); // pass texture if needed
    Dog donnie(donnie_image,{100,300});
    currentLevel->setDog(&donnie);


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
        //input
        currentLevel->handleInput();

        //update
        currentLevel->update(deltaTime);


        //Drawing
        window.clear();
        view = update(view,donnie);
        window.setView(view);
        window.draw(backgroundSprite);
        currentLevel->draw(window);
        window.display();

        // if (currentLevel->isComplete()) {
        //     donnie.setPosition({0,0});
        //     currentLevel = std::make_unique<TestLevel>(); // or however you're sequencing
        //     std::cout<<"am reusit!!";
        //     currentLevel->setDog(&donnie);
        // }
    }
}


/**

#include "Functii.cpp"
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Donnie the Doggie");
    window.setFramerateLimit(60);
    sf::Texture texture("hole.jpg", false, sf::IntRect({0, 0}, {1200, 600})); // Throws sf::Exception if an error occurs

    sf::Texture donnie_image("donsprite.png", false, sf::IntRect({0, 0}, {87, 51}));
    sf::Sprite sprite(texture);

    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));//ASTA-I PT SCROLLING VIEW
    window.setView(view);

    Dog donnie(donnie_image,{100.f,300.f});
    sf::Clock clock;
    std::vector<Wall> walls;
    walls.push_back(Wall(sf::Vector2f(300, 400), sf::Vector2f(50, 200)));
    walls.push_back(Wall(sf::Vector2f(500, 300), sf::Vector2f(50, 150)));
    walls.push_back(Wall(sf::Vector2f(0,550),sf::Vector2f(2000,50)));
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();

        donnie.update(deltaTime,walls);
        view = update(view,donnie);
        window.setView(view);
        window.clear();

        // draw everything here...
        window.draw(sprite);
        donnie.draw(window);
        for (Wall& wall : walls)
            wall.draw(window);
        // end the current frame
        window.display();
    }
}



**/