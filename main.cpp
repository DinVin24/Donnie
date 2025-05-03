#include "Functii.cpp"
#include <SFML/Graphics.hpp>
#include <memory>

/**
 * TODO: Health system
 * TODO: Save best times
 * TODO: Obstacles for each level that can hurt u
 * TODO: forest level, train level, town level
 * TODO: end screen
 */
int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Donnie the Doggie");
    window.setFramerateLimit(60);
    sf::Texture donnie_image("walking1.png", false, sf::IntRect({0, 0}, {100, 100}));

    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));
    window.setView(view);

    sf::Clock clock;
    sf::Clock globalClock;
    sf::Time cronometru;

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
        cronometru = globalClock.getElapsedTime();
        std::cout<<(int)cronometru.asSeconds()<<'\n';
        window.clear();
        view = update(view,donnie);
        window.setView(view);
        window.draw(backgroundSprite);
        currentLevel->draw(window);
        window.display();

        if (currentLevel->isComplete()) {
            donnie.setPosition({100,100});
            std::cout << "am reusit!!\n";
            if (currentLevel->getNivel() == -1)
                currentLevel = std::make_unique<TestLevel>();
            else
                currentLevel = std::make_unique<LevelOne>();
            currentLevel->setDog(&donnie);
            currentLevel->load();
            backgroundSprite = sf::Sprite(currentLevel->getBackground());
        }
    }
}
//macar 3 nivele, sa sara pe niste garduri, sa care ceva de undeva, ai nevoie de un obiectiv clar!!
//o misiune ceva, poti sa faci si sa treaca de o strada, adauga obstacole care probabil sa se miste, sa mosteneasca entity
//refa miscarea ca nu arata natural
//incearca sa pui un timer macar, sa memorezi timpurile si cel mai bun, speedrun idk

//ok deci cred ca cel mai cool ar fi sa adaug un timer ca sa te intreci cu altii i guess.
//o sa am 3 nivele lungi, de 3 ori cat lungimea ecranului
//primul nivel este in padure
//al doilea nivel este in
//al treilea nivel este in oras, unde chiar isi gaseste stapanul
