#pragma once

class PainGiver : public Wall {
public:
    PainGiver(sf::Vector2f position, sf::Vector2f size)
        : Wall(position, size) {
        shape.setFillColor(sf::Color::Transparent);
    }

    friend std::ostream& operator<<(std::ostream& os, const PainGiver& obj) {
        os << "POZ: " << obj.getPosition().x << ' ' << obj.getPosition().y << '\n';
        return os;
    }

};

