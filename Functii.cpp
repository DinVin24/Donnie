#include <SFML/Graphics.hpp>
#include "Dog.h"
#include "Wall.h"
#include "TestLevel.h"
#include <iostream>
#include "SFML/Audio/Listener.hpp"
bool Dog::onGround(const std::vector<Wall>& walls) {
    sf::FloatRect dbounds = getBounds();
    bool stanga = false, dreapta = false;
    for (const Wall& wall:walls) {
        sf::FloatRect wbounds = wall.getBounds();
        for (float x = dbounds.position.x; x <= dbounds.position.x+dbounds.size.x;x++) {
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
        velocity.y = -jumpHeight;
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
            std::cout<<"COLLISIION \n";
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
sf::View update(sf::View view, Dog dog) {
    int window_height = 600;
    int window_width = 800;
    struct {int x=2000,y=800;}level_size;//hardcodat for testing purposes
    if (dog.getPosition().x >= window_width / 2 )
        view.setCenter({dog.getPosition().x,window_height / 2});
    if (dog.getPosition().x >= level_size.x - window_width / 2 )
        view.setCenter({level_size.x - window_width / 2, window_height / 2});
    return view;
}