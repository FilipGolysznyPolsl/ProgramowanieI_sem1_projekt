#pragma once

#include<iostream>

#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Sprite sprite;

	sf::Vector2f direction;
	float movementSpeed;
public:
	// Constructor and deconstructor
	Bullet(sf::Texture* texture, float position_x, float position_y, float direction_x, float direction_y, float movement_speed, float scale = 1.f);
	~Bullet();

	// Public variables
	bool destroyed;

	// Accessor for bullet position
	const sf::Vector2f& getPosition();

	// Public functions
	void update();
	void render(sf::RenderTarget& target);
};

