#include "Functii.cpp"
#include <SFML/Graphics.hpp>
#include <memory>

int main() {
    try {
        //initializare fereastra
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Donnie the Doggie");
        window.setFramerateLimit(60);
        sf::Texture donnie_image("walking1.png", false, sf::IntRect({0, 0}, {100, 100}));
        sf::Texture healthTexture("donnie_face.png",false,sf::IntRect({0,0},{58,50}));
        sf::Sprite heartSprite(healthTexture);
        sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));
        window.setView(view);
        //gata initializare fereastra

        //TIMER:
        sf::Font fontTimer("pricedown.ttf");
        sf::Text timerText(fontTimer);
        timerText.setCharacterSize(35);
        timerText.setOutlineThickness(2);
        timerText.setFont(fontTimer);
        timerText.setFillColor(sf::Color::White);
        timerText.setOutlineColor(sf::Color::Black);
        timerText.setPosition({view.getCenter().x-390,view.getCenter().y-290});
        sf::Clock clock;
        sf::Clock globalClock;
        sf::Time cronometru;
        //GATA TIMER

        //initializare meniu si caine
        std::unique_ptr<Nivele> currentLevel = std::make_unique<Menu>();
        Dog donnie(donnie_image,{100,300});
        currentLevel->setDog(&donnie);
        currentLevel->load();
        sf::Sprite backgroundSprite(currentLevel->getBackground());
        //gata initializare meniu si caine

        //main game loop
        while (window.isOpen()) {
            debugPrint(donnie);
            debugPrint(currentLevel->getWalls());
            debugPrint(currentLevel->getPainGivers());
            Debugger<Dog>::pause(donnie);
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
            timerText.setPosition({view.getCenter().x-390,10.f});
            if ((int) cronometru.asSeconds() % 60 != (int) globalClock.getElapsedTime().asSeconds() % 60){
                std::ostringstream ss;
                cronometru = globalClock.getElapsedTime();
                if ((int)cronometru.asSeconds()/60 != 0 )
                    ss<<(int)cronometru.asSeconds()/60<<':';
                if ((int)cronometru.asSeconds()%60<10) ss<<0;
                ss<<(int)cronometru.asSeconds()%60;
                timerText.setString(ss.str());
            }
            //HEALTH
            window.clear();
            view = update(view,donnie,currentLevel->getNivel());
            window.setView(view);
            window.draw(backgroundSprite);
            currentLevel->draw(window);
            window.draw(timerText);

            heartSprite.setPosition({view.getCenter().x + 390, 30.f}); // 10 px from left, 50 px from top
            for (int i = 0; i < donnie.getHealth(); ++i) {
                heartSprite.setPosition({view.getCenter().x + 332 - i * (heartSprite.getGlobalBounds().size.x + 5), 30.f});
                window.draw(heartSprite);
            }
            window.display();

            //AVANSAREA IN NIVELE
            if (currentLevel->isComplete()) {
                donnie.setPosition({100,100});
                if (currentLevel->getNivel() == -1)
                    currentLevel = std::make_unique<LevelOne>();
                else if (currentLevel->getNivel() == 1)
                    currentLevel = std::make_unique<LevelTwo>();
                else if (currentLevel->getNivel() == 2)
                    currentLevel = std::make_unique<VictoryScreen>();
                currentLevel->setDog(&donnie);
                currentLevel->load();
                backgroundSprite = sf::Sprite(currentLevel->getBackground());
            }
            else if (currentLevel->getGameOver()) {
                donnie.setPosition({100,100});
                donnie.setHealth(3);
                globalClock.restart();
                std::cout << "AI PIERDUT!";
                currentLevel = std::make_unique<Menu>();
                currentLevel->setDog(&donnie);
                currentLevel->load();
                backgroundSprite = sf::Sprite(currentLevel->getBackground());
            }
        }
        //gata main game loop
    } catch (const GameException& e) {
        std::cerr << "EROARE: " << e.what() << std::endl;
        return 1;
    }
}
//adauga instructiuni la inceput!!
//explica ce se intampla, ce sunt vietile, ce face cronometrul


/*
main.cpp -  keeps the main game loop, renders the window, time, literally does everything obviously.
functii.cpp - i write longer functions there to keep my classes kinda clean
Entity.h - pretty self explanatory, it has basic functions such as input handling, updating on screen, getTexture,
setPosition, getPosition, getBounds
Dog.h - inherits enitity, this one's big, it keeps the speed, textures, basically every property my dog has.
it also handles movement, gravity, life, states
Wall.h - just a sprite i throw on the screen. The dog checks by itself if there's any wall that it collides with.
PainGiver.h - inherits walls, but this time if there's a collision with the dog, it takes damage.
Nivele.h - only used for inheritance, has the basic load functions, input handling, screen updating, win or lose state
Menu.h / VictoryScreen.h- just one/two buttons on the screen to either exit or start. it inherits nivele.h
LevelOne/Two/Three.h - all of these inherit nivele.h, and they overload the methods from nivele. in the load()
function they spawn the dog and create a walls and a paingiver list where they push these obstacles so the dog
can just call the list for the collision checks. they all have different end conditions and stuff

so when you open the game, menu.h is loaded, the dog is loaded too and is on screen. when you press start game,
the new level is loaded, all obstacles are placed accordingly and the dog is teleported to its new position.
same thing happens when you advance to the next level.
*/