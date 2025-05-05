#include "Functii.cpp"
#include <SFML/Graphics.hpp>
#include <memory>

int main() {
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
    std::unique_ptr<Nivele> currentLevel = std::make_unique<Menu>(); // pass texture if needed
    Dog donnie(donnie_image,{100,300});
    currentLevel->setDog(&donnie);
    currentLevel->load();
    sf::Sprite backgroundSprite(currentLevel->getBackground());
    //gata initializare meniu si caine

    //main game loop
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
            std::cout <<"CURRENT LEVEL:"<<currentLevel->getNivel() << "\n";
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
