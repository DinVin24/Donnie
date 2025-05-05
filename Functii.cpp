#include <SFML/Graphics.hpp>
#include "Dog.h"
#include "Wall.h"
#include "PainGiver.h"
#include "TestLevel.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "Menu.h"
#include "VictoryScreen.h"
#include <iostream>
#include "SFML/Audio/Listener.hpp"
bool Dog::onGround(const std::vector<Wall>& walls) {
    sf::FloatRect dbounds = getBounds();
    bool stanga = false, dreapta = false;
    for (const Wall& wall:walls) {
        sf::FloatRect wbounds = wall.getBounds();
        for (float x = dbounds.position.x; x <= dbounds.position.x+dbounds.size.x;x ++) {
            if (wbounds.position.y + 1 >= dbounds.position.y + dbounds.size.y &&
                wbounds.position.y - 2 <= dbounds.position.y + dbounds.size.y &&
                x >= wbounds.position.x && x <= wbounds.position.x + wbounds.size.x ) {
                return true;
            }
        }
    }
    return false;

}
void Dog::handleInput(const std::vector<Wall>& walls)  {
//cu functia asta miscam cainele
    velocity.x = 0.f;
    direction.x = 0;
    int bothPressed = 0; //verifica daca A si D sunt apasate simultan
    iAmRunning = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && am_voie.stanga) {
        velocity.x -= speed;
        direction.x = -1;
        bothPressed ++;
        iAmRunning = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && am_voie.dreapta) {
        velocity.x += speed;
        direction.x = 1;
        bothPressed ++;
        iAmRunning = !iAmRunning;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && onGround(walls)) {
        velocity.y = -jumpHeight;
        direction.y = -1;
        momentum = sf::seconds(0.35f);//cat dureaza un salt
    }
    if (bothPressed == 2) direction.x = 0;
    animateMovement();
}

void Dog::fall(const std::vector<Wall>& walls) {
    if (!onGround(walls)) {
        if (momentum > sf::seconds(0))momentum -= sf::seconds(0.016f);
        else {
            momentum = sf::seconds(0);
            velocity.y = fallSpeed;
            direction.y = 1;
        }
    }
}
void Dog::checkCollisions(const std::vector<Wall>& walls) {
    //     .left	.position.x
    //      .top	.position.y
    //    .width	.size.x
    //   .height	.size.y
    for (const Wall& wall:walls) {
        sf::FloatRect dbounds = getBounds();
        sf::FloatRect wbounds = wall.getBounds();
        if (dbounds.findIntersection(wbounds)) {
            // std::cout<<"COLLISIION \n";
            if(direction.x == -1){
                // std::cout<<"left\n";
                direction.x = 0;
                velocity.x = 0;
                am_voie.stanga = false;
                // move({5,0});
                setPosition({wbounds.position.x+wbounds.size.x+1,dbounds.position.y});
            }
            else am_voie.stanga = true;
            if(direction.x == 1){
                // std::cout<<"right\n";
                direction.x = 0;
                velocity.x = 0;
                am_voie.dreapta = false;
                // move({-5,0});
                setPosition({wbounds.position.x-dbounds.size.x-1,dbounds.position.y});
            }else am_voie.dreapta = true;
            if(direction.y == -1) {
                //sus
                velocity.y = 0;
                // move({0,5});
                setPosition({dbounds.position.x, wbounds.position.y + wbounds.size.y + 1});
                momentum = sf::seconds(0);

            }
            if (direction.y == 1) {//jos
                // move({0,-2});
                setPosition({dbounds.position.x, wbounds.position.y - dbounds.size.y - 1});
                velocity.y = 0;
            }
        }
        else {
            am_voie.stanga = am_voie.dreapta = true;
        }
    }
}
void Dog::checkDamage(const std::vector<PainGiver>& paingivers) {
    if (getPosition().y>600) {
        health--;
        setPosition({30,350});
    }
    if (invincibility <= 0 )
        for (const PainGiver& paingiver:paingivers) {
            if (getBounds().findIntersection(paingiver.getBounds())) {
                health--;
                invincibility = 75;
            }
        }
    else if (invincibility > 0) invincibility --;

}
void Dog::update(float deltaTime, const std::vector<Wall>& walls, const std::vector<PainGiver>& paingivers) {
    float debugx=velocity.x,debugy=velocity.y;
    handleInput(walls);// aici ne miscam
    sprite.move(velocity ); // * deltaTime
    fall(walls);
    checkCollisions(walls);
    checkDamage(paingivers);
    // if (velocity.x!=debugx || velocity.y!=debugy)
        // std::cout<<"VELOCITY: "<<velocity.x<<"    "<<velocity.y<<std::endl;
}
sf::View update(sf::View view, Dog dog,int level) {
    float window_height = 600;
    float window_width = 800;
    struct {float x=2400,y=600;} level_size;//hardcodat for testing purposes
    if (level < 1 || level > 3)level_size.x=800;
    if (dog.getPosition().x >= window_width / 2 )
        view.setCenter({dog.getPosition().x,window_height / 2});
    else view.setCenter({400,300});
    if (dog.getPosition().x >= level_size.x - window_width / 2 )
        view.setCenter({level_size.x - window_width / 2, window_height / 2});
    return view;
}
void Dog::animateMovement() {
    if (velocity.y!=0) {
        //ANIMATIE SALT
        if (frame>=60)frame = 60;
        if (frame<25)setTexture(jump1);
        else if (frame<45)setTexture(jump2);
        else if (frame<60)setTexture(jump3);
        frame++;

    }
    else if (iAmRunning) {
        //ANIMATIE MERS

        if (frame>=60)frame = 0;
        if (frame < 10)setTexture(walk1);
        else if (frame < 20)setTexture(walk2);
        else if (frame < 30)setTexture(walk3);
        else if (frame < 40)setTexture(walk4);
        else if (frame < 50)setTexture(walk5);
        else if (frame < 60)setTexture(walk6);
        frame++;

    }
    else {
        frame = 0;
        setTexture(walk1);
        // setTexture(defaultStance);
    }
}