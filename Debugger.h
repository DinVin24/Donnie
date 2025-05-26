#pragma once

template <typename T>
class Debugger {
public:

    static const std::string typeName;

    static void print (const T& obj) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
            sf::sleep(sf::milliseconds(30));
            std::cout <<"----- "<< typeName << '\n';
            std::cout << obj << '\n';
        }
    }
    static void print(const std::vector<T>& vec) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
            sf::sleep(sf::milliseconds(25));
            std::cout <<"----- "<< typeName << '\n';
            for (const auto& elem : vec)
                std::cout << elem << '\n';
        }
    }

    static void pause (const T& obj) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
            sf::sleep(sf::milliseconds(100));
            while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
                print(obj);
                sf::sleep(sf::milliseconds(100));
            }
            sf::sleep(sf::milliseconds(100));
        }
    }

    friend void debugPrint (const T& obj);

};
template <typename T>
const std::string Debugger<T>::typeName = typeid(T).name();
