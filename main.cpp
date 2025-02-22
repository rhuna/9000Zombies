// 9000Zombies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"



int main(){
    sf::Texture texture;
    texture.loadFromFile("./graphics/player.png");
   
    Player player(texture);



}

