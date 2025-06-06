#pragma once

#include "SFML/Graphics.hpp"
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
#include "Debugger.h"
#include "LevelFactory.h"
#include "HealthObserver.h"
#include "HealthDisplay.h"
#include "Instructiuni.h"

bool Dog::onGround(const std::vector<Wall>& walls) {
    //verifica daca Dog este pe un Wall
    sf::FloatRect dbounds = getBounds();
    float stanga = dbounds.position.x;
    float dreapta = dbounds.position.x + getBounds().size.x;
    for (const Wall& wall:walls) {
        sf::FloatRect wbounds = wall.getBounds();
        if (stanga <= wbounds.position.x + wbounds.size.x && dreapta >= wbounds.position.x &&
            wbounds.position.y + 1 >= dbounds.position.y + dbounds.size.y &&
            wbounds.position.y - 2 <= dbounds.position.y + dbounds.size.y)
            return true;
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
        // ne miscam la stanga
        velocity.x -= speed;
        direction.x = -1;
        bothPressed ++;
        iAmRunning = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && am_voie.dreapta) {
        // ne miscam la dreapta
        velocity.x += speed;
        direction.x = 1;
        bothPressed ++;
        iAmRunning = !iAmRunning;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && velocity.y == 0) {
        //sarim
        velocity.y = -jumpHeight;
        direction.y = -1;
        momentum = sf::seconds(0.35f);//cat dureaza un salt
    }
    if (bothPressed == 2) direction.x = 0;
    animateMovement();
}

void Dog::fall(const std::vector<Wall>& walls) {
    //daca nu sunt pe un Wall si nici in timpul unui salt, cad
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
    //cauta intersectie intre caine si orice Wall
    for (const Wall& wall:walls) {
        sf::FloatRect dbounds = getBounds();
        sf::FloatRect wbounds = wall.getBounds();
        if (dbounds.findIntersection(wbounds)) {
            if(direction.x == -1){ //intersectie in stanga cainelui
                direction.x = 0;
                velocity.x = 0;
                am_voie.stanga = false;
                setPosition({wbounds.position.x+wbounds.size.x+1,dbounds.position.y});
            }
            else am_voie.stanga = true;
            if(direction.x == 1){ //intersectie in dreapta cainelui
                direction.x = 0;
                velocity.x = 0;
                am_voie.dreapta = false;
                setPosition({wbounds.position.x-dbounds.size.x-1,dbounds.position.y});
            }else am_voie.dreapta = true;
            if(direction.y == -1) { // intersectie deasupra cainelui
                velocity.y = 0;
                setPosition({dbounds.position.x, wbounds.position.y + wbounds.size.y + 1});
                momentum = sf::seconds(0);

            }
            if (direction.y == 1) {// intersectie sub caine
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
    // daca am cazut din nivel sau atingem un PainGiver, se scade viata
    // si avem un timp scurt de invincibilitate
    if (getPosition().y>600) {
        setHealth(health-1);
        setPosition({30,350});
    }
    if (invincibility <= 0 )
        for (const PainGiver& paingiver:paingivers) {
            if (getBounds().findIntersection(paingiver.getBounds())) {
                setHealth(health-1);
                invincibility = 75;
            }
        }
    else if (invincibility > 0) invincibility --;
}
void Dog::update(float deltaTime, const std::vector<Wall>& walls, const std::vector<PainGiver>& paingivers) {
    // aici sunt apelate functiile de mai sus
    handleInput(walls);
    sprite.move(velocity);
    fall(walls);
    checkCollisions(walls);
    checkDamage(paingivers);
}
sf::View update(sf::View view, Dog dog,int level) {
    // aici se modifica pozitia camerei, ca sa urmareasca cainele
    // totusi daca ajungem prea aproape de marginea nivelului, camera ramane pe loc
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
template <typename T>
void debugPrint(const T& obj) {
    Debugger<T>::print(obj);
}
template <typename T>
void debugPrint(const std::vector<T>& vec) {
    Debugger<T>::print(vec);
}
