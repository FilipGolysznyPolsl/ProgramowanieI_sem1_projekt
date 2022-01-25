#include "Explosion.h"

// Constructor, also initializes variables
Explosion::Explosion(sf::Texture* texture, sf::Vector2f position)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(position);
	this->sprite.setScale(2.f, 2.f);
	this->timer = 0;
	this->setTime = 6;
}

// Deconstructor
Explosion::~Explosion()
{
}

// Return number of frame animetion should be set to
int Explosion::frameNumber()
{
	if (this->timer % this->setTime == 0)
	{
		return static_cast<int>(this->timer / 6);
	}
	else
	{
		return 0;
	}
}

// Change sprite - frame in animation
void Explosion::changeFrame(sf::Texture* texture)
{
	this->sprite.setTexture(*texture);
}

// Measure time to keep track of animations
void Explosion::passTime()
{
	this->timer += 1;
	if (this->timer > 40)
	{
		this->timer = 0;
	}
}

// Render function
void Explosion::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
