#include "Bullet.h"
#include "TextureHolder.h"


Bullet::Bullet() :
	m_bulletdistanceX(0.0f), m_bulletdistanceY(0.0f), 
	m_maxX(100.0f), m_maxY(100.0f),m_minX(1.0f),m_minY(1.0f)
{
	m_bulletshape.setSize(sf::Vector2f(2, 2));
	std::cout<<"bullet created\n";
}
Bullet::~Bullet() {
    // Destructor implementation
	std::cout << "bullet deleted\n";
}


void Bullet::stop() {
	m_inflight = false;
};
bool Bullet::isInFlight() {
	return m_inflight;
};
void Bullet::shoot(float startX, float startY, float targetX, float targetY) {
	m_inflight = true;
	m_position.x = startX;
	m_position.y = startY;
	float gradient = (startX - targetX) / (startY - targetY);
	if (gradient < 0) {
		gradient *= -1;
	}
	float ratioXY = m_bulletspeed / (1 + gradient);
	m_bulletdistanceX = ratioXY;
	m_bulletdistanceY = ratioXY * gradient;
	if (targetX < startX) {
		m_bulletdistanceX *= -1;
	}
	if (targetY < startY) {
		m_bulletdistanceY *= -1;
	}
	float range = 1000;
	m_maxX = range;
	m_maxY = range;
	m_minX = 0;
	m_minY = 0;
	m_bulletshape.setPosition(m_position);
};
sf::FloatRect Bullet::getPosition() {
	return m_bulletshape.getGlobalBounds();
};
sf::RectangleShape Bullet::getShape() {
	return m_bulletshape;
};
void Bullet::update(float elapsedTime) {
	m_position.x += m_bulletdistanceX * elapsedTime;
	m_position.y += m_bulletdistanceY * elapsedTime;
	m_bulletshape.setPosition(m_position);
	if (m_position.x < m_minX || m_position.x > m_maxX || m_position.y < m_minY || m_position.y > m_maxY) {
		m_inflight = false;
	}

};
