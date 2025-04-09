#include <SFML/Graphics.hpp>
#include "Dog.h"
#include "Wall.h"
#include <iostream>
#include "SFML/Audio/Listener.hpp"
bool Dog::onGround(const std::vector<Wall>& walls) {
    sf::FloatRect dbounds = getBounds();
    for (const Wall& wall:walls) {
        sf::FloatRect wbounds = wall.getBounds();
        if ((dbounds.position.x >= wbounds.position.x && dbounds.position.x <= wbounds.position.x + wbounds.size.x) &&
            dbounds.position.x + dbounds.size.x <= wbounds.position.x + wbounds.size.x &&
    ///AAAAH MODIFICA CONDITIILE DE AICI CA TE CONTRAZICI

            dbounds.position.y+dbounds.size.y >= wbounds.position.y - 2) {
            // std::cout<<dbounds.position.y+dbounds.size.y<<' '<<wbounds.position.y<<'\n';
            return true;
        }
    }
    return false;
}
void Dog::handleInput(const std::vector<Wall>& walls)  {
//cu functia asta miscam cainele
    velocity.x = 0.f;
    direction.x = 0;
    int bothPressed = 0; //verifica daca A si D sunt apasate simultan
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && am_voie.stanga) {
        velocity.x -= speed;
        direction.x = -1;
        bothPressed ++;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && am_voie.dreapta) {
        velocity.x += speed;
        direction.x = 1;
        bothPressed ++;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && onGround(walls)) {
        velocity.y = -800.f;
        direction.y = -1;
        momentum = sf::seconds(0.30f);//cat dureaza un salt
    }
    if (bothPressed == 2) direction.x = 0;
}
void Dog::fall(const std::vector<Wall>& walls) {
    if (!onGround(walls)) {
        if (momentum > sf::seconds(0))momentum -= sf::seconds(0.016f);
        else {
            momentum = sf::seconds(0);
            velocity.y = 500.f;//viteza de cadere
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
            std::cout<<"COLLISIION ";
            if(direction.x == -1){
                // std::cout<<"left\n";
                direction.x = 0;
                velocity.x = 0;
                am_voie.stanga = false;
                move({5,0});
            }
            else am_voie.stanga = true;
            if(direction.x == 1){
                // std::cout<<"right\n";
                direction.x = 0;
                velocity.x = 0;
                am_voie.dreapta = false;
                move({-5,0});
            }else am_voie.dreapta = true;
            if(direction.y == -1) {
                // std::cout<<"up\n";
            }
            if (direction.y == 1) {
                move({0,-2});
                velocity.y = 0;
            }
        }
        else {
            am_voie.stanga = am_voie.dreapta = true;
        }
    }
}
void Dog::update(float deltaTime, const std::vector<Wall>& walls) {
    float debugx=velocity.x,debugy=velocity.y;
    handleInput(walls);// aici ne miscam
    sprite.move(velocity * deltaTime); //aici chiar ne miscam, actualizam pozitii, chestii
    fall(walls);
    checkCollisions(walls);
    if (velocity.x!=debugx || velocity.y!=debugy)
        std::cout<<"VELOCITY: "<<velocity.x<<"    "<<velocity.y<<std::endl;
}