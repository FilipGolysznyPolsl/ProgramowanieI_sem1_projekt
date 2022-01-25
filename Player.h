#pragma once

#include<iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

// Player class to keep track of player and player movement
class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float movementSpeed;

	// Private functions
	void initTexture();
	void initSprite();
public:
	Player();
	~Player();

	// Set and get
		// Size of player
	sf::Vector2f& getSize();
		// Position of the player
	void setPosition(float x, float y);
	const sf::Vector2f& getPosition();

	// Player public functions
	void move(const float direction_x, const float direction_y);
	
	void render(sf::RenderTarget& target);
};

