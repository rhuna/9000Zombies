#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player(const sf::Texture& playerTexture) :
	m_sprite(playerTexture), m_tileSize(15)
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_maxHealth = START_HEALTH;

	m_upPressed=false;
	m_downPressed = false;
	m_leftPressed = false;
	m_rightPressed = false;

	//associate a texture with the sprite
	m_sprite.setTexture(m_texture);

	//set origin
	//for more accurate set to center of player
	m_sprite.setOrigin({ -25,-100 });
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize) {
	m_position.x = arena.position.x / 2;
	m_position.y = arena.position.y / 2;

	//copy details of the arena to players m_arena
	m_arena = arena;
	m_tileSize = tileSize;

	m_resolution.x = resolution.x;
	m_resolution.y = resolution.y;

};
//call this at the end of everygame
void Player::resetPlayerStats() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_maxHealth = START_HEALTH;
};
bool Player::hit(sf::Time timeHit) {
	if (timeHit.asMilliseconds() - m_lastHit.asMilliseconds() > 200) {
		m_lastHit = timeHit;
		m_Health -= 10;
		return true;
	}else {
		return false;
	}
};
sf::Time Player::getLastTimeHit() {
	return m_lastHit;
};
//get player position
sf::FloatRect Player::getPosition() {
	return m_sprite.getGlobalBounds();
};
//where is the center of the player
sf::Vector2f Player::getCenter() {
	return m_position;
};
//what angle is the player facing
sf::Angle Player::getRotation() {// need to figure this out need a way to convert to angle.
	return m_sprite.getRotation();
};
//send copy of sprite to the main function
sf::Sprite Player::getSprite() {
	return m_sprite;
};

void Player::moveRight() {
	m_rightPressed = true;
};
void Player::moveLeft() {
	m_leftPressed = true;
};
void Player::moveUp() {
	m_upPressed = true;
};
void Player::moveDown() {
	m_downPressed = true;
};
void Player::stopRight() {
	m_rightPressed = false;
};
void Player::stopLeft() {
	m_leftPressed = false;
};
void Player::stopUp() {
	m_upPressed = false;
};
void Player::stopDown() {
	m_downPressed = false;
};
sf::Vector2f Player::getposition() {
	return m_position;
};
sf::IntRect Player::getarena() {
	return m_arena;
};
sf::Vector2f Player::getresolution() {
	return m_resolution;
};
//will call this function once every frame
void Player::update(float elapsedTime, sf::Vector2i mousePosition) {
	if (m_upPressed) {
		m_position.y -= m_Speed * elapsedTime;
	}
	if (m_downPressed) {
		m_position.y += m_Speed * elapsedTime;
	}
	if (m_rightPressed) {
		m_position.x += m_Speed * elapsedTime;
	}
	if (m_leftPressed) {
		m_position.x -= m_Speed * elapsedTime;
	}
	m_sprite.setPosition(m_position);
	
	//keep the player in the arena
	//right side of screen
	if (m_position.x > 1900 - m_tileSize) {
		m_position.x = 1900 - m_tileSize;
	}
	//left side of the screen
	if (m_position.x < 100 - m_tileSize) {
		m_position.x = 100 - m_tileSize;
	}
	//bottom side of screen
	if (m_position.y > 1000 - m_tileSize) {
		m_position.y = 1000 - m_tileSize;
	}
	//top of the screen
	if (m_position.y < 100 - m_tileSize) {
		m_position.y = 100 - m_tileSize;
	}
	float angle = std::atan2(mousePosition.y - m_resolution.y / 2.0f, mousePosition.x - m_resolution.x / 2.0f);
	sf::Angle angle2 = sf::degrees(angle);
	m_sprite.setRotation(angle2);
};

//give player a speed boost
void Player::upgradeSpeed() {
	m_Speed += (START_SPEED * 0.2f);

};

//give player some health
void Player::upgradeHealth() {
	m_maxHealth += (START_HEALTH * 0.2f);
};

//increase the maximum amount of the health player can have
void Player::increaseHealthLevel(int amount) {
	m_maxHealth += amount;
	//but not beyond maximum
	if (m_Health > m_maxHealth) {
		m_Health = m_maxHealth;
	}
};

//how much health does the player currently have
int Player::getHealth() {
	return m_Health;
};