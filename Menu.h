class MenuLevel : public Level {
private:
    sf::Font font;
    sf::Text title;
    sf::Text startOption;
    bool readyToStart = false;

public:
    MenuLevel() {
        font.loadFromFile("arial.ttf"); // Or your own font
        title.setFont(font);
        title.setString("Donnie the Doggie");
        title.setCharacterSize(48);
        title.setPosition(200.f, 150.f);

        startOption.setFont(font);
        startOption.setString("Press Enter to Start");
        startOption.setCharacterSize(24);
        startOption.setPosition(250.f, 300.f);
    }

    void handleInput() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            readyToStart = true;
        }
    }

    void update(float) override {}

    void draw(sf::RenderWindow& window) override {
        window.draw(title);
        window.draw(startOption);
    }

    bool isComplete() const override {
        return readyToStart;
    }

    void setDog(Dog&) override {} // Not needed here
};
