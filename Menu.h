class Menu : public Nivele {
    bool exit=false,start=false;
public:

    void load() override {
        nivel = -1;
        backgroundTexture.loadFromFile("menu.jpg");
        dog->setPosition({400, 300});
        walls.push_back(Wall({0, 600}, {800, 2}));
        walls.push_back(Wall({-4,0},{4,600}));
        walls.push_back(Wall({800,0},{4,600}));
    }

    void handleInput(sf::RenderWindow& window) override {
        sf::IntRect s ({321,312},{170,81});
        sf::IntRect e ({350,430},{108,67});
        dog->handleInput(walls);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            sf::Vector2i poz = sf::Mouse::getPosition(window);
            if (e.contains(poz)) exit = true;
            if (s.contains(poz)) start = true;
        }
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
        return start;
    }
    bool getExit() const override {
        return exit;
    }
    sf::Texture& getBackground(){return this->backgroundTexture;}
};
