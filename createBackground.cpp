//#include "Zombie_arena.h"	
//#include <cstdlib> // For rand() and srand()
//#include <ctime>   // For time()


//int createBackground(sf::VertexArray& rVA, sf::IntRect arena) {
//	//anything we do to the rVA will be done to the background
//	//tile/texture size
//	const int TILE_SIZE = 50;
//	const int TILE_TYPES = 6;
//	const int VERTS_IN_TRIANGLES = 6;
//
//	int worldWidth = 750 / TILE_SIZE;
//	int worldHeight = 750 / TILE_SIZE;
//
//	rVA.setPrimitiveType(sf::PrimitiveType::Triangles);
//	rVA.resize(worldWidth * worldHeight * VERTS_IN_TRIANGLES);
//
//	//START AT THE BEGINNING OF THE VERTEX ARRAY
//	int currentVertex = 0;
//
//	for (int w = 0; w < worldWidth; w++) {
//		for (int h = 0; h < worldHeight; h++) {
//			// Triangle 1: Top-left, Top-right, Bottom-right
//			rVA[currentVertex + 0].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE); // Top-left
//			rVA[currentVertex + 1].position = sf::Vector2f((w + 1) * TILE_SIZE, h * TILE_SIZE); // Top-right
//			rVA[currentVertex + 2].position = sf::Vector2f((w + 1) * TILE_SIZE, (h + 1) * TILE_SIZE); // Bottom-right
//
//			// Triangle 2: Bottom-right, Bottom-left, Top-left
//			rVA[currentVertex + 3].position = sf::Vector2f((w + 1) * TILE_SIZE, (h + 1) * TILE_SIZE); // Bottom-right
//			rVA[currentVertex + 4].position = sf::Vector2f(w * TILE_SIZE, (h + 1) * TILE_SIZE); // Bottom-left
//			rVA[currentVertex + 5].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE); // Top-left
//
//			// Texture coordinate assignment
//			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1) {
//				// Wall texture for edges
//				for (int i = 0; i < VERTS_IN_TRIANGLES; ++i) {
//					rVA[currentVertex + i].texCoords = sf::Vector2f(0, TILE_SIZE * 2); // Assuming wall texture is at this offset
//				}
//			}
//			else {
//				// Random floor texture
//				int verticalOffset = (std::rand() % TILE_TYPES) * TILE_SIZE;
//				for (int i = 0; i < VERTS_IN_TRIANGLES; ++i) {
//					rVA[currentVertex + i].texCoords = sf::Vector2f(0, verticalOffset); // Get texture from vertical offset
//				}
//			}
//			currentVertex += VERTS_IN_TRIANGLES;
//		}
//	};
//	return TILE_SIZE;
//}
 
#include "Zombie_arena.h"	
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

	int createBackground(sf::VertexArray & rVA, sf::IntRect arena) {
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
