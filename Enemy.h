#pragma once

#include<SFML/Graphics.hpp>

class Enemy
{
private:
	sf::Sprite sprite;
	
	float movementSpeed;
	float direction_x;
	float rowPosition;
public:
	Enemy(sf::Texture* texture);
	~Enemy();

	// Public variables
	bool destroyed;

	// Position accessor
	const sf::Vector2f& getPosition();
	sf::Vector2f& getSize();

	// Functions
	void changeDirection();
	void moveToSide();
	void moveDown();
	bool isMovedDown();
	void updateRow();
	
	void render(sf::RenderTarget& target);
};

