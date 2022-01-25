#include "Player.h"

// Set player texture and check if succesfullly loaded
void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/player.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Cannot load texture from file" << "\n";
	}
}

void Player::initSprite()
{
	// Set sprite texture
	this->sprite.setTexture(this->texture);
	// Set sprite scale
	this->sprite.scale(2.f, 2.f);
}

// Constructor
Player::Player()
{
	this->movementSpeed = 2.f;
	this->initTexture();
	this->initSprite();
}

// Empty deconstructor - no memory alocation in player
Player::~Player()
{
}

// Getter function for size
sf::Vector2f& Player::getSize()
{
	sf::FloatRect player_bounds = this->sprite.getGlobalBounds();
	sf::Vector2f size;
	size.x = player_bounds.width;
	size.y = player_bounds.height;
	return size;
}

// Setter function to set player position
void Player::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

// Getter function for position
const sf::Vector2f& Player::getPosition()
{
	return this->sprite.getPosition();
}

// Move player
void Player::move(const float direction_x, const float direction_y)
{
	this->sprite.move(direction_x * this->movementSpeed, direction_y * movementSpeed);
}

// Render player on target view or window
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
