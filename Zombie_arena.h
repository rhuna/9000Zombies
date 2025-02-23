#pragma once

#ifndef ZOMBIE_ARENA_H
#define ZOMBIE_ARENA_H

#include "Zombie.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>


int createBackground(sf::VertexArray& rVA, sf::IntRect arena);
Zombie* createHorde(int numZombies, sf::IntRect arena);


#endif // !ZOMBIE_ARENA_H


