#include "Functii.cpp"

int main() {
    try {
        //initializare fereastra
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Donnie the Doggie");
        window.setFramerateLimit(60);
        sf::Texture donnie_image("walking1.png", false, sf::IntRect({0, 0}, {100, 100}));
        sf::Texture healthTexture("donnie_face.png",false,sf::IntRect({0,0},{58,50}));
        HealthDisplay healthDisplay(healthTexture);
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
        donnie.addObserver(&healthDisplay);
        sf::Sprite backgroundSprite(currentLevel->getBackground());
        //gata initializare meniu si caine

        //main game loop
        while (window.isOpen()) {
            debugPrint(donnie); // apasam tasta O pentru a afisa informatii
            debugPrint(currentLevel->getWalls()); // apasam tasta I
            debugPrint(currentLevel->getPainGivers()); // aici tot tasta I
            // Debugger<Dog>::pause(donnie); // apasam tassta P
            while (const std::optional event = window.pollEvent()) {
                // aici ii dam voie utilizatorului sa inchida fereastra
                if (event->is<sf::Event::Closed>() || currentLevel->getExit())
                    window.close();
            }
            float deltaTime = clock.restart().asSeconds();

            //Drawing

            //Pozitionam si actualizam timer-ul
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
            window.clear();
            view = update(view,donnie,currentLevel->getNivel());
            window.setView(view);
            window.draw(backgroundSprite);
            currentLevel->runLevel(window,deltaTime);
            window.draw(timerText);
            healthDisplay.draw(window,view);
            window.display();

            //AVANSAREA IN NIVELE
            if (currentLevel->isComplete()) {
                donnie.setPosition({100,100});
                currentLevel = createNextLevel(currentLevel->getNivel());
                currentLevel->setDog(&donnie);
                currentLevel->load();
                backgroundSprite = sf::Sprite(currentLevel->getBackground());
            }
            else if (currentLevel->getGameOver()) {
                donnie.setPosition({100,100});
                donnie.setHealth(3);
                globalClock.restart();
                std::cout << "AI PIERDUT!";
                currentLevel = createNextLevel(0);
                currentLevel->setDog(&donnie);
                currentLevel->load();
                backgroundSprite = sf::Sprite(currentLevel->getBackground());
            }
        }
        //gata main game loop
    } catch (const GameException& e) { // prindem ce erori avem de prins
        std::cerr << "EROARE: " << e.what() << std::endl;
        return 1;
    }
}
