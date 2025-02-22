// 9000Zombies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"



int main(){



    sf::Texture texture;
    texture.loadFromFile("./graphics/player.png");
   
    Player player(texture);

    sf::VideoMode vm = sf::VideoMode::getFullscreenModes()[0];
    sf::RenderWindow window(vm, "zombies");


    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        window.clear();
        window.draw(player.getSprite());
        window.display();
    }



}

