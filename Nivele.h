#pragma once

class Nivele {
protected:
    std::vector<Wall> walls;
    std::vector<PainGiver> paingivers;
    sf::Texture wallTexture, enemyTexture, dogTexture,backgroundTexture;
    Dog* dog;
    bool exit = false;
    bool gameover = false;
    int nivel;

public:
    virtual ~Nivele() {}

    void setDog(Dog* newdog){dog = newdog;};
    virtual void load() = 0;
    virtual void handleInput(sf::RenderWindow &window) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual bool isComplete() const = 0;
    virtual bool getExit() const = 0;
    const std::vector<Wall>& getWalls() const {
        return walls;
    }
    const std::vector<PainGiver>& getPainGivers() const {
        return paingivers;
    }
    bool getGameOver() const {return gameover;}
    virtual sf::Texture& getBackground(){return backgroundTexture;}
    void setNivel(int newNivel){nivel = newNivel;}
    int getNivel(){return nivel;}

    void runLevel(sf::RenderWindow &window, float dt) {
        handleInput(window);
        update(dt);
        draw(window);


    }

};
