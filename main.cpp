#include "Functii.cpp"
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Donnie the Doggie");
    window.setFramerateLimit(60);

    sf::Texture texture("hole.jpg", false, sf::IntRect({0, 0}, {800, 600})); // Throws sf::Exception if an error occurs
    sf::Texture donnie_image("donsprite.png", false, sf::IntRect({0, 0}, {87, 51}));
    sf::Sprite sprite(texture);

    Dog donnie(donnie_image,{100.f,300.f});
    sf::Clock clock;

    std::vector<Wall> walls;
    walls.push_back(Wall(sf::Vector2f(300, 400), sf::Vector2f(50, 200)));
    walls.push_back(Wall(sf::Vector2f(500, 300), sf::Vector2f(50, 150)));
    walls.push_back(Wall(sf::Vector2f(0,550),sf::Vector2f(800,50)));
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();

        donnie.update(deltaTime,walls);

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