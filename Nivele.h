class Nivele {
protected:
    std::vector<Wall> walls;
    sf::Texture wallTexture, enemyTexture, dogTexture,backgroundTexture;
    Dog* dog;

public:
    virtual ~Nivele() {}

    void setDog(Dog* newdog){dog = newdog;};
    virtual void load() = 0; // pure virtual: each level must implement its own loader
    virtual void handleInput() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual bool isComplete() const = 0; // used to check if we move to the next level
    virtual sf::Texture& getBackground(){return backgroundTexture;}
};