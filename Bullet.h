#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "SFML/Graphics.hpp"


class Bullet{
public:
	
	Bullet();
	void stop();
	bool isInFlight();
	void shoot(float startX, float startY, float targetX, float targetY);
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
	void update(float elapsedTime);
	~Bullet();



private:
	sf::Vector2f m_position;
	sf::RectangleShape m_bulletshape;
	
	bool m_inflight = false;

	float m_bulletspeed = 1000;


	float m_bulletdistanceX;
	float m_bulletdistanceY;

	float m_maxX;
	float m_maxY;
	float m_minX;
	float m_minY;


};

#endif // !BULLET_H



