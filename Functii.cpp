#include <SFML/Graphics.hpp>
#include "Dog.h"
#include "Wall.h"
#include "SFML/Audio/Listener.hpp"

// Function to handle input
void Dog::handleInput()  {
    velocity.x = 0.f;
    direction.x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        velocity.x = -200.f;
        direction.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        velocity.x = 200.f;
        direction.x = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && onGround == true) {
        velocity.y = -300.f;
        direction.y = -1;
        onGround = false;
        momentum = sf::seconds(0.5f);
    }
    fall();
}
void Dog::fall() {
    float G = 150.f; //constanta gravitationala lol
    if (momentum > sf::seconds(0))momentum -= sf::seconds(0.016f);
    if (momentum <= sf::seconds(0) && onGround == false) {
        velocity.y = G;
        direction.y = 1;
        momentum = sf::seconds(0.f);
    }

}
void checkCollisions(Dog& dog, const std::vector<Wall>& walls) {
//     .left	.position.x
//      .top	.position.y
//    .width	.size.x
//   .height	.size.y
    for (const Wall& wall : walls) {
        sf::FloatRect dbounds = dog.getBounds();
        sf::FloatRect wbounds = wall.getBounds();
        if (dbounds.findIntersection(wbounds)) {
            sf::Vector2f v = dog.getVelocity();
            int dx = dog.getDirection().x;
            int dy = dog.getDirection().y;
            //CAZUL IN CARE AM ZID IN DREAPTA
            if (dx == 1) {
                dog.setVelocity({-20.,v.y});
                dx = 0;
            }
            //CAZUL IN CARE AM ZID IN STANGA
            if (dx == -1) {
                dog.setVelocity({20.,v.y});
                dx = 0;
            }
            // CAZUL IN CARE AM ZID JOS
             if (dy == 1) {
                 dog.setVelocity({v.x,-1.});
                 dy = 0;
                 dog.setOnGround(true);
             }
             //CAZUL IN CARE AM ZID SUS
             if (dy == -1) {
                 dog.setVelocity({v.x,20.});
                 dy = 0;
             }
            dog.setDirection(dx,dy);

        }
    }
}
/**
 * IDK  man this shit kinda hard, look over what u did in 11th grade i guess
 *
 ***/
