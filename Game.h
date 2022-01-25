#pragma once

#include<sstream>

#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include"Explosion.h"

/* Game class to handle whole game mechanics*/
class Game
{
private:
	// Game window
	int gameHeight;
	int gameWidth;
	sf::RenderWindow* window;

	// Variables
		// general
	int points;
	int health;
	int maxEnemies;
		//shooting
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	float enemyShootTimer;
	float enemyShootTimerMax;
	float menuTextTimer;
	float spaceHoldTimer;
		// booleans
	bool spaceHold;
	bool endGame;
	bool gameOngoing;
	bool gameWon;
		// text
	sf::Font font;
	sf::Text uiText;
	sf::Text menuText;
	sf::Text titleText;

	// Textures adn vectors
		// Bullets
	sf::Texture* bulletTexture;
	sf::Texture* enemyBulletTexture;
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> enemyBullets;
		// Enemies
	sf::Texture* enemyTexture[4];
	std::vector<Enemy*> enemies;
		// Explosions
	std::vector<Explosion*> explosions;

	// Player pointer
	Player* player;

	// Private functions
	void initWindow();
	void initFont();
	void initText();
	void initVariables();
	void resetVariables();
	void initTextures();
	void initPlayer();

	void enemyFireTimeReset();
public:
	// Constructor and deconstructor
	Game();
	~Game();

	void resetGame();
	
	// Functions
	void run();
		// Update user input
	void pollEvents();
	void updateInput();
		// Enemies and bullets
	void spawnEnemies();
	void updateEnemies();
	void enemyFire();
	void updateBullets();
		// Collisions
	void updateDamage();
	void updateExplosions();

	void updateText();
	void update();
	void menuUpdate();

	// Rendering
	void renderBullets();
	void renderEnemies();
	void renderExplosions();
	void renderText(sf::RenderTarget& target);
	void render();

	void renderMenuText(sf::RenderTarget& target);
	void menuRender();
};

