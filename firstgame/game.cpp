#include "game.h"

//private function
void game::initVariables()
{
	this->window = nullptr;

	//game logic
	
	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}


void game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;
	this->window = new sf::RenderWindow(this->videomode, "game 1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void game::initEnemies()
{
	this->enemy.setPosition(50.f,50.f);
	this->enemy.setSize(sf::Vector2f(100.f,100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);


}


// constructor / destructor
game::game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

game::~game() {
	delete this->window;
}

const bool game::running() const
{
	return this->window->isOpen();
}



//functions

void game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets their colors and positions.
		-Sets a random position,
		-Sets a random color.
		-Adds enemy to the vector.
	*/


}

void game::pollEvents()
{
	//event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
		}
	}
}

void game::updateMousePosition()
{
	/*
		update the mouse position
		- mouse position relative to window (vec2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void game::update()
{
	this->pollEvents();

	this->updateMousePosition();
	
	this->updateEnemies();
}

void game::updateEnemies()
{
	/**
		@return void

		updatre the enemy spawn timer and spawns enemies
		when the total amout of enemies is smaller than the maximu.
	*/
	//updating the timer for enemy spawing
	if(this->enemies.size()<this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}
}

void game::render()
{
	/*
	*	clear old frame
	*	render object
	*	display frame in window
	*	
	*	Renders the game object
	*/
	this->window->clear(sf::Color());

	//draw game
	this->renderEnemies();
	this->window->display();

}

void game::renderEnemies()
{
}


