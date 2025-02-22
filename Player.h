#pragma once
#ifndef PLAYER_H

#include<iostream>
#include<SFML/Graphics.hpp>


class Player{
public:
	
	Player(const sf::Texture &playerTexture);
	void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
	//call this at the end of everygame
	void resetPlayerStats();
	bool hit(sf::Time timeHit);
	sf::Time getLastTimeHit();
	//get player position
	sf::FloatRect getPosition();
	//where is the center of the player
	sf::Vector2f getCenter();
	//what angle is the player facing
	sf::Angle getRotation();
	//send copy of sprite to the main function
	sf::Sprite getSprite();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void stopRight();
	void stopLeft();
	void stopUp();
	void stopDown();

	//will call this function once every frame
	void update(float elapsedTime, sf::Vector2i mousePosition);

	//give player a speed boost
	void upgradeSpeed();

	//give player some health
	void upgradeHealth();

	//increase the maximum amount of the health player can have
	void increaseHealthLevel(int amount);

	//how much health does the player currently have
	int getHealth();

	sf::Vector2f getposition();
	sf::IntRect getarena();
	sf::Vector2f getresolution();
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	//player position
	sf::Vector2f m_position;

	//sprite texture
	sf::Texture m_texture;

	//player sprite
	sf::Sprite m_sprite;


	//screen resolution
	sf::Vector2f m_resolution;

	//size of the current arena
	sf::IntRect m_arena;

	//how big each tile of the arena is
	int m_tileSize;

	//which direction is the player moving
	bool m_upPressed;
	bool m_downPressed;
	bool m_leftPressed;
	bool m_rightPressed;

	//how much health does the player have
	float m_Health;
	//max health
	float m_maxHealth;

	// when was the player last hit
	sf::Time m_lastHit;

	//speed in pixels per second
	float m_Speed;
};



#endif // !PLAYER_H



