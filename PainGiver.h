#ifndef PAINGIVER_HPP
#define PAINGIVER_HPP

class PainGiver : public Wall {
public:
    PainGiver(sf::Vector2f position, sf::Vector2f size)
        : Wall(position, size) {
        shape.setFillColor(sf::Color::Transparent); // or set texture later
    }

};

#endif