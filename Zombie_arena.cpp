#include "Zombie_arena.h"

	
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

int createBackground(sf::VertexArray& rVA, sf::IntRect arena) {
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 6;
	const int VERTS_IN_TRIANGLES = 6;

	int worldWidth = arena.position.x / TILE_SIZE;
	int worldHeight = arena.position.y / TILE_SIZE;

	rVA.setPrimitiveType(sf::PrimitiveType::Triangles);
	rVA.resize(worldWidth * worldHeight * VERTS_IN_TRIANGLES);

	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++) {
		for (int h = 0; h < worldHeight; h++) {
			rVA[currentVertex + 0].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = sf::Vector2f((w + 1) * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 2].position = sf::Vector2f((w + 1) * TILE_SIZE, (h + 1) * TILE_SIZE);

			rVA[currentVertex + 3].position = sf::Vector2f((w + 1) * TILE_SIZE, (h + 1) * TILE_SIZE);
			rVA[currentVertex + 4].position = sf::Vector2f(w * TILE_SIZE, (h + 1) * TILE_SIZE);
			rVA[currentVertex + 5].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);

			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1) {
				for (int i = 0; i < VERTS_IN_TRIANGLES; ++i) {
					rVA[currentVertex + i].texCoords = sf::Vector2f(0, TILE_SIZE * 2);
				}
			}
			else {
				int verticalOffset = (std::rand() % TILE_TYPES) * TILE_SIZE;
				rVA[currentVertex + 0].texCoords = sf::Vector2f(0, verticalOffset);
				rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, verticalOffset);
				rVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE, verticalOffset + TILE_SIZE);
				rVA[currentVertex + 3].texCoords = sf::Vector2f(TILE_SIZE, verticalOffset + TILE_SIZE);
				rVA[currentVertex + 4].texCoords = sf::Vector2f(0, verticalOffset + TILE_SIZE);
				rVA[currentVertex + 5].texCoords = sf::Vector2f(0, verticalOffset);
			}

			currentVertex += VERTS_IN_TRIANGLES;
		}
	}
	return TILE_SIZE;
}

Zombie* createHorde(int numZombies, sf::IntRect arena) {

	Zombie* zombies = new Zombie[numZombies];


	int maxY = arena.position.y + 1;
	int minY = arena.position.y - 1000;
	int maxX = arena.position.x + 1;
	int minX = arena.position.x - 1000;



	for (int i = 0; i < numZombies; i++) {
		//which side should the zombie spawn
		std::srand((int)time(0) * i);
		int side = (std::rand() % 4);
		float x = 0, y = 0;
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