#include "Bullet.h"

// Constructor with initialization
Bullet::Bullet(sf::Texture* texture, float position_x, float position_y, float direction_x, float direction_y, float movement_speed, float scale)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(position_x, position_y);
	this->sprite.setScale(1.f, scale);
	this->direction.x = direction_x;
	this->direction.y = direction_y;
	this->movementSpeed = movement_speed;
	this->destroyed = false;
}

// Deconstructor
Bullet::~Bullet()
{
}

// Getter function for position
const sf::Vector2f& Bullet::getPosition()
{
	return this->sprite.getPosition();
}

// Update bullet movement
void Bullet::update()
{
	this->sprite.move(this->direction * this->movementSpeed);
}

// Render bullet object on target view or window
void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
