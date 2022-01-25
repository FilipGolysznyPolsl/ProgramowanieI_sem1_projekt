#include "Enemy.h"

// Costructor of enemy class, initialization of variables
Enemy::Enemy(sf::Texture* texture)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(1.f, 1.f);
	this->sprite.setScale(2.f,2.f);
	this->movementSpeed = 1.f;
	this->direction_x = 1.f;
	this->rowPosition = this->sprite.getPosition().y;
	this->destroyed = false;
}

// Deconstructor
Enemy::~Enemy()
{
}

// Getter function for position
const sf::Vector2f& Enemy::getPosition()
{
	return this->sprite.getPosition();
}

// Getter function for size
sf::Vector2f& Enemy::getSize()
{
	sf::FloatRect enemy_bounds = this->sprite.getGlobalBounds();
	sf::Vector2f size;
	size.x = enemy_bounds.width;
	size.y = enemy_bounds.height;
	return size;
}

// Change enemy horizontal direction
void Enemy::changeDirection()
{
	this->direction_x *= -1;
}

// Move enemy from side to side of the window
void Enemy::moveToSide()
{
	this->sprite.move(this->direction_x * this->movementSpeed, 0.f);
}

// Move enmemy down, to next row
void Enemy::moveDown()
{
	this->sprite.move(0.f, 1.f * this->movementSpeed);
}

// Check if enemy moved a full row, from current row
bool Enemy::isMovedDown()
{
	if (this->sprite.getPosition().y == this->rowPosition + 32)
	{
		return true;
	}
	else
	{
		return false;
	}

}

// Record which row is enemy at
void Enemy::updateRow()
{
	this->rowPosition = this->sprite.getPosition().y;
}

// Render enemy
void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
