#include "Zombie_arena.h"


Zombie* createHorde(int numZombies, sf::IntRect arena) {

	Zombie* zombies = new Zombie[numZombies];


	int maxY = arena.position.y+1;
	int minY = arena.position.y-1000;
	int maxX = arena.position.x+1;
	int minX = arena.position.x-1000;



	for (int i = 0; i < numZombies; i++) {
		//which side should the zombie spawn
		std::srand((int)time(0) * i);
		int side = (std::rand() % 4);
		float x=0, y=0;
		switch (side) {
			case 1:
				//left
				x = minX;
				y = (std::rand() % maxY) + minY;
				break;
			case 2:
				//right
				x = maxX;
				y = (std::rand() % maxY) + minY;
				break;
			case 3:
				//top
				x = (std::rand() % maxX) + minX;
				y = minY;
				break;
			case 4:
				//bottom
				x = (std::rand() % maxX) + minX;
				y = maxY;
				break;

		}

		//bloater, crawler or runner
		std::srand((int)time(0) * i * 2);
		int type = (std::rand() % 3);

		zombies[i].spawn(x, y, type, i);
	}


	return zombies;
};
