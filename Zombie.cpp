#include "Zombie.h"
#include "TextureHolder.h"


Zombie::Zombie() :
	m_Sprite(m_texture), m_Alive(true), m_Health(100)
{

	spawn(m_Position.x, m_Position.y, 2, 32);
};


bool Zombie::hit() {
	m_Health--;
	if (m_Health < 0) {
		//dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::getTexture("./graphics/blood.png"));
		return true;
	}
	return false;
};
bool Zombie::isAlive() {
	return m_Alive;
};
void Zombie::spawn(float startX, float startY, int type, int seed) {
	switch (type) {
	case 0:
		//bloater
		m_Sprite = sf::Sprite(TextureHolder::getTexture("./graphics/bloater.png"));
		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		break;
	case 1:
		//chaser
		m_Sprite = sf::Sprite(TextureHolder::getTexture("./graphics/chaser.png"));
		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		break;
	case 2:
		//crawler
		m_Sprite = sf::Sprite(TextureHolder::getTexture("./graphics/crawler.png"));
		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;
	};

	//MODIFY THE SPEED TO MAKE THE ZOMBIE UNIQUE
	//CREATE A SPEED MODIFIER
	std::srand((int)time(0) * seed);
	//const int MAX_VARIANCE = 66;
	//const int OFFSET = 123 - MAX_VARIANCE;
	float modifier = (std::rand() % MAX_VARIANCE) + OFFSET +0.1f;
	modifier /= 100;
	m_Speed *= modifier;
	m_Position.x = startX;
	m_Position.y = startY;
	m_Sprite.setOrigin({ 25, 25 });
	m_Sprite.setPosition(m_Position);
};
sf::FloatRect Zombie::getPosition(){
	return m_Sprite.getGlobalBounds();
};
sf::Sprite Zombie::getSprite(){
	return m_Sprite;
};
void Zombie::update(float elapsedTime, sf::Vector2f playerLocation) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	//update zombie position to follow player
	if (playerX > m_Position.x) {
		m_Position.x = m_Position.x + m_Speed * elapsedTime;
	}
	if (playerY > m_Position.y) {
		m_Position.y = m_Position.y + m_Speed * elapsedTime;
	}
	if (playerX < m_Position.x) {
		m_Position.x = m_Position.x - m_Speed * elapsedTime;
	}
	if (playerY > m_Position.y) {
		m_Position.y = m_Position.y - m_Speed * elapsedTime;
	}
	m_Sprite.setPosition(m_Position);

	float angle1 = (std::atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / 3.141;
	sf::Angle angle(sf::degrees(angle1));
	m_Sprite.setRotation(angle);

};