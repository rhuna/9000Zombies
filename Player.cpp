#include "Player.h"


Player::Player(const sf::Texture &playerTexture){

	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_maxHealth = START_HEALTH;

	//associate a texture with the sprite
	m_texture = playerTexture;
	m_sprite.setTexture(m_texture);

	//set origin
	//for more accurate set to center of player
	m_sprite.setOrigin({ 25,25 });
}

void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize) {

};
//call this at the end of everygame
void resetPlayerStats() {

};
bool hit(sf::Time timeHit) {

};
sf::Time getLastTimeHit() {

};
//get player position
sf::FloatRect getPosition() {

};
//where is the center of the player
sf::Vector2f getCenter() {

};
//what angle is the player facing
float getRotation() {

};
//send copy of sprite to the main function
sf::Sprite getSpriet() {

};