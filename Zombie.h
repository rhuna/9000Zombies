#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

class Zombie{
public:

	//handle hit of zombie by bullet
	Zombie();
	~Zombie();
	bool hit();
	bool isAlive();
	void spawn(float startX, float startY, int type, int seed);
	sf::FloatRect getPosition();
	sf::Sprite getSprite();
	void update(float elapsedTime, sf::Vector2f playerLocation);




private:

	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;

	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	//MAKE EACH ZOMBIE VARRY IT SPEED SLIGHTLY
	const int MAX_VARIANCE = 66;
	const int OFFSET = 123 - MAX_VARIANCE;

	//zombie position
	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	sf::Texture m_texture;
	float m_Speed;
	float m_Health;

	bool m_Alive;


};


#endif // !ZOMBIE_H



