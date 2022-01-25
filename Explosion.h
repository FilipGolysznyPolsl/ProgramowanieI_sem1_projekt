#pragma once

#include<SFML/Graphics.hpp>

class Explosion
{
private:
	sf::Sprite sprite;
	int timer;
	int setTime;
public:
	Explosion(sf::Texture* texture, sf::Vector2f position);
	~Explosion();

	// Functions
	int frameNumber();
	void changeFrame(sf::Texture* texture);
	void passTime();

	void render(sf::RenderTarget& target);
};

