#include "Functii.cpp"
#include <SFML/Graphics.hpp>
#include <memory>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Donnie the Doggie");
    window.setFramerateLimit(60);
    sf::Texture donnie_image("donsprite.png", false, sf::IntRect({0, 0}, {87, 51}));

    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));
    window.setView(view);

    sf::Clock clock;

    std::unique_ptr<Nivele> currentLevel = std::make_unique<Menu>(); // pass texture if needed
    Dog donnie(donnie_image,{100,300});
    currentLevel->setDog(&donnie);
    currentLevel->load();
    sf::Sprite backgroundSprite(currentLevel->getBackground());


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>() || currentLevel->getExit())
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
        //input
        currentLevel->handleInput(window);

        //update
        currentLevel->update(deltaTime);


        //Drawing
        window.clear();
        view = update(view,donnie);
        window.setView(view);
        window.draw(backgroundSprite);
        currentLevel->draw(window);
        window.display();

        if (currentLevel->isComplete()) {
            donnie.setPosition({100,100});
            std::cout << "am reusit!!\n";
            currentLevel = std::make_unique<TestLevel>();
            currentLevel->setDog(&donnie);
            currentLevel->load();
            backgroundSprite = sf::Sprite(currentLevel->getBackground());
        }
    }
}
