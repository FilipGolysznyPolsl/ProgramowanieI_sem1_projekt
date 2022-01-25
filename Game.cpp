#include "Game.h"


// Initialize game window
void Game::initWindow()
{
	this->gameHeight = 600;
	this->gameWidth = 800;
	this->window = new sf::RenderWindow(sf::VideoMode(this->gameWidth, this->gameHeight), "Filip Golyszny - Projekt", sf::Style::Default);
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/RobotoMono-Regular.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONT::Failed to load font" << "\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
	this->uiText.setPosition(0.f, 500.f);

	this->menuText.setFont(this->font);
	this->menuText.setCharacterSize(24);
	this->menuText.setFillColor(sf::Color::White);
	this->menuText.setString("NONE");
	this->menuText.setPosition(200.f, 350.f);

	this->titleText.setFont(this->font);
	this->titleText.setCharacterSize(55);
	this->titleText.setFillColor(sf::Color::White);
	this->titleText.setString("NONE");
	this->titleText.setPosition(50.f, 200.f);
}

// Initialize game variables
void Game::initVariables()
{
	std::srand(static_cast<unsigned>(time(NULL)));

	this->points = 0;
	this->health = 3;
	this->maxEnemies = 100;
	this->enemyShootTimer = 0.f;
	this->enemyShootTimerMax = 100.f;
	this->enemySpawnTimerMax = 40.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->menuTextTimer = 0.f;
	this->spaceHoldTimer = 0.f;
	this->spaceHold = false;
	this->endGame = false;
	this->gameOngoing = false;
	this->gameWon = false;
}

void Game::resetVariables()
{
	this->points = 0;
	this->health = 3;
	this->menuTextTimer = 0.f;
	this->spaceHoldTimer = 0.f;
	this->enemyShootTimer = 0.f;
	this->enemyShootTimerMax = 100.f;
	this->enemySpawnTimerMax = 40.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->gameWon = false;
}

void Game::initTextures()
{
	// Load bullet textures
	this->bulletTexture = new sf::Texture;
	if (!this->bulletTexture->loadFromFile("Textures/bullet.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Cannot load bullet texture from file" << "\n";
	}
	this->enemyBulletTexture = new sf::Texture;
	if (!this->enemyBulletTexture->loadFromFile("Textures/enemy_bullet.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Cannot load enemy bullet texture from file" << "\n";
	}

	// Load enemy textures
	this->enemyTexture[0] = new sf::Texture;
	if (!this->enemyTexture[0]->loadFromFile("Textures/invader.png", sf::IntRect(0, 0, 32, 32)))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Cannot load enemy texture[0] from file" << "\n";
	}
	this->enemyTexture[1] = new sf::Texture;
	if (!this->enemyTexture[1]->loadFromFile("Textures/invader.png", sf::IntRect(32, 0, 32, 32)))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Cannot load enemy texture[1] from file" << "\n";
	}
	this->enemyTexture[2] = new sf::Texture;
	if (!this->enemyTexture[2]->loadFromFile("Textures/invader.png", sf::IntRect(0, 32, 32, 32)))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Cannot load enemy texture[2] from file" << "\n";
	}
	this->enemyTexture[3] = new sf::Texture;
	if (!this->enemyTexture[3]->loadFromFile("Textures/invader.png", sf::IntRect(32, 32, 32, 32)))
	{
		std::cout << "ERROR::GAME::INITTEXTURES::Cannot load enemy texture[3] from file" << "\n";
	}
}

// Initialize player and set position
void Game::initPlayer()
{
	this->player = new Player;
	this->player->setPosition(static_cast<float>(this->gameWidth) / 2.f, static_cast<float>(this->gameHeight) - 50);
}

void Game::enemyFireTimeReset()
{
	this->enemyShootTimer = 0.f;
	this->enemyShootTimerMax = 50 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (200 - 50)));
}

// Constructor - initializes object
Game::Game()
{
	this->initFont();
	this->initText();
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initPlayer();
}

// deconstructor - frees all alocated memory
Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->bulletTexture;
	delete this->enemyBulletTexture;
	for (int i = 0; i < 4; i++) {
		delete this->enemyTexture[i];
	}
	// Empty all vectors
	while (enemies.size() > 0)
	{
		this->enemies.erase(this->enemies.begin());
	}
	while (bullets.size() > 0)
	{
		this->bullets.erase(this->bullets.begin());
	}
	while (enemyBullets.size() > 0)
	{
		this->enemyBullets.erase(this->enemyBullets.begin());
	}
	while (explosions.size() > 0)
	{
		this->explosions.erase(this->explosions.begin());
	}
}

void Game::resetGame()
{
	// Empty all vectors
	while (enemies.size() > 0)
	{
		this->enemies.erase(this->enemies.begin());
	}
	while (bullets.size() > 0)
	{
		this->bullets.erase(this->bullets.begin());
	}
	while (enemyBullets.size() > 0)
	{
		this->enemyBullets.erase(this->enemyBullets.begin());
	}
	while (explosions.size() > 0)
	{
		this->explosions.erase(this->explosions.begin());
	}
}

// Main game loop
void Game::run()
{
	while (this->window->isOpen())
	{
		if (this->gameOngoing == false)
		{
			this->menuUpdate();
			this->menuRender();
		}
		else
		{
			this->update();
			this->render();
		}
	}
}

// Check if game was closed
void Game::pollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
		}
	}
}

// Check for input from keyboard
void Game::updateInput()
{
	// Allow player to move sideways, provided he isn't on edge of the screen
	if (this->player->getPosition().x > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->player->move(-1.f, 0.f);
		}
	}
	if (this->player->getPosition().x < this->gameWidth - this->player->getSize().x)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->player->move(1.f, 0.f);
		}
	}

	// Shoot a bullet if space is pressed, but not id it's held down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->spaceHold == false)
		{
			this->spaceHold = true;
			this->bullets.push_back(new Bullet(
				this->bulletTexture,
				this->player->getPosition().x, this->player->getPosition().y,
				0.f, -1.f,
				2.f
			));
		}
	}
	else
	{
		if (this->spaceHoldTimer >= 50)
		{
			this->spaceHoldTimer = 0.f;
			this->spaceHold = false;
		}
		else
		{
			this->spaceHoldTimer += 1.f;
		}
	}
}

// Spawn enemies if there are not enough on screen
void Game::spawnEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.push_back(new Enemy(this->enemyTexture[0]));
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}
}

// Manage enemy movement
void Game::updateEnemies()
{
	for (auto* enemy : enemies)
	{
		// Move down a row if enemy is on edge of the screen, and change side to side direction
		if (enemy->getPosition().x == 0 || enemy->getPosition().x == gameWidth - enemy->getSize().x)
		{
			if (enemy->isMovedDown())
			{
				enemy->changeDirection();
				enemy->updateRow();
				enemy->moveToSide();
			}
			else
			{
				enemy->moveDown();
			}
		}
		else
		{
			enemy->moveToSide();
		}
	}
}

// Fire bullets form random enemy on random intervals
void Game::enemyFire()
{
	if (this->enemyShootTimer >= this->enemyShootTimerMax)
	{
		int i = rand() % (this->enemies.size() - 1);
		this->enemyBullets.push_back(new Bullet(
			this->enemyBulletTexture,
			this->enemies[i]->getPosition().x - this->enemies[i]->getSize().x/2, this->enemies[i]->getPosition().y + this->enemies[i]->getSize().y,
			0.f, 1.f,
			3.f,
			-1.f
		));
		this->enemyFireTimeReset();
	}
	else
	{
		this->enemyShootTimer += 2.f + (this->enemies.size() / (0.05 * this->maxEnemies));
	}
}

// Move bullets, and delete them if outside of game window
void Game::updateBullets()
{
	// Player bullets
	for (int i=0; i < this->bullets.size(); i++)
	{
		bullets[i]->update();

		if (bullets[i]->getPosition().y < 0 || bullets[i]->getPosition().y > gameHeight)
		{
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
	// Enemy bullets
	for (int i = 0; i < this->enemyBullets.size(); i++)
	{
		enemyBullets[i]->update();

		if (enemyBullets[i]->getPosition().y < 0 || enemyBullets[i]->getPosition().y > gameHeight)
		{
			this->enemyBullets.erase(this->enemyBullets.begin() + i);
		}
	}
}

// Check if bullets hit player or enemies
void Game::updateDamage()
{
	// Enemy bullets
	for (int i = 0; i < this->enemyBullets.size(); i++)
	{
		if (enemyBullets[i]->getPosition().y > this->player->getPosition().y + 36 && enemyBullets[i]->getPosition().y < this->player->getPosition().y + this->player->getSize().y)
		{
			if (enemyBullets[i]->getPosition().x > this->player->getPosition().x - 5 && enemyBullets[i]->getPosition().x < this->player->getPosition().x + this->player->getSize().x - 10)
			{
				this->enemyBullets.erase(this->enemyBullets.begin() + i);
				this->health -= 1;
				if (this->health <= 0)
				{
					this->endGame = true;
					this->gameOngoing = false;
				}
			}
		}
	}
	// Player bullets
	for (int i = 0; i < this->bullets.size(); i++)
	{
		for (int j = 0; j < this->enemies.size(); j++)
		{
			if (this->bullets[i]->getPosition().y > this->enemies[j]->getPosition().y && this->bullets[i]->getPosition().y < this->enemies[j]->getPosition().y + this->enemies[j]->getSize().y - 30)
			{
				if (this->bullets[i]->getPosition().x > this->enemies[j]->getPosition().x && this->bullets[i]->getPosition().x < this->enemies[j]->getPosition().x + this->enemies[j]->getSize().x - 30)
				{
					this->bullets[i]->destroyed = true;
					this->explosions.push_back(new Explosion(this->enemyTexture[1], enemies[j]->getPosition()));
					this->enemies[j]->destroyed = true;
					this->points += 1;
					if (this->points >= 100)
					{
						this->endGame = true;
						this->gameOngoing = false;
						this->gameWon = true;
					}
				}
			}
		}
	}
	// Erase destroyed bullets and enemies
	for (int i = 0; i < this->bullets.size(); i++)
	{
		if (this->bullets[i]->destroyed == true)
		{
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
	for (int i = 0; i < this->enemies.size(); i++)
	{
		if (this->enemies[i]->destroyed == true)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

// Animate explosions, and erase finished
void Game::updateExplosions()
{
	for (int i = 0; i < explosions.size(); i++)
	{
		switch (explosions[i]->frameNumber())
		{
		case 0:
			explosions[i]->passTime();
			break;
		case 1:
			explosions[i]->changeFrame(this->enemyTexture[2]);
			explosions[i]->passTime();
			break;
		case 2:
			explosions[i]->changeFrame(this->enemyTexture[2]);
			explosions[i]->passTime();
			break;
		case 3:
			explosions[i]->changeFrame(this->enemyTexture[3]);
			explosions[i]->passTime();
			break;
		case 4:
			this->explosions.erase(this->explosions.begin() + i);
			break;
		}
	}

}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n";

	this->uiText.setString(ss.str());
}

// Update game state
void Game::update()
{
	this->pollEvents();
	this->updateInput();
	this->spawnEnemies();
	this->updateEnemies();
	this->enemyFire();
	this->updateBullets();
	this->updateExplosions();
	this->updateDamage();
	this->updateText();
}

// Handle menu text and starting game on spacebar
void Game::menuUpdate()
{
	std::string blinking;

	// Poll for closing the game
	this->pollEvents();

	// set title or game over message
	if (this->endGame == false)
	{
		this->titleText.setString("Inwazja");
		this->titleText.setPosition(275.f, 200.f);

		blinking = "Nacisnij spacje aby strzelic";
	}
	else if (this->gameWon == false)
	{
		this->titleText.setString("Przegrales, koniec gry");
		this->titleText.setPosition(35.f, 200.f);

		blinking = "Nacisnij spacje aby zagrac ponownie";
		this->menuText.setPosition(150.f, 350.f);
	}
	else
	{
		this->titleText.setString("Wygrales, gratulacje!");
		this->titleText.setPosition(50.f, 200.f);

		blinking = "Nacisnij spacje aby zagrac ponownie";
		this->menuText.setPosition(150.f, 350.f);
	}
	// Display blinking text
	if (this->menuTextTimer <= 80)
	{
		this->menuText.setString(blinking);
	}
	else
	{
		this->menuText.setString("");
	}
	if (this->menuTextTimer >= 120)
	{
		this->menuTextTimer = 0.f;
	}
	this->menuTextTimer += 1.f;


	// Start game on space press
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->gameOngoing = true;
		this->endGame = false;
		this->resetVariables();
		this->resetGame();
	}
}


// Rendering functions
void Game::renderBullets()
{
	for (auto* bullet : this->bullets)
	{
		bullet->render(*this->window);
	}
	for (auto* bullet : this->enemyBullets)
	{
		bullet->render(*this->window);
	}
}

void Game::renderEnemies()
{
	for (auto* enemy : enemies)
	{
		enemy->render(*this->window);
	}
}

void Game::renderExplosions()
{
	for (auto* explosion : explosions)
	{
		explosion->render(*this->window);
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::render()
{
	// Clear window before rendering
	this->window->clear();

	// Render all game objects
	this->player->render(*this->window);
	this->renderEnemies();
	this->renderBullets();
	this->renderExplosions();
	this->renderText(*this->window);

	// Display rendered objects
	this->window->display();
}

void Game::renderMenuText(sf::RenderTarget& target)
{
	target.draw(this->titleText);
	target.draw(this->menuText);
}

void Game::menuRender()
{
	// Clear window before rendering
	this->window->clear();

	this->renderMenuText(*this->window); 

	// Display rendered objects
	this->window->display();
}
