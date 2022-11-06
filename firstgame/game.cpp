#include "game.h"

//private function
void game::initVariables()
{
	this->window = nullptr;

	//game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
}

void game::initFonts()
{
	if (this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
	}
}

void game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(14);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
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
	this->enemy.setPosition(10.f,10.f);
	//this->enemy.setSize(sf::Vector2f(100.f,100.f));
	//this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);


}


// constructor / destructor
game::game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

game::~game() {
	delete this->window;
}

const bool game::running() const
{
	return this->window->isOpen();
}

const bool game::getEndGame() const
{
	return this->endGame;
}



//functions

void game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets their types, colors and positions.
		-Sets a randem type(diff)
		-Sets a random position,
		-Sets a random color.
		-Adds enemy to the vector.
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), //Sets a random position
		0.f
	);

	//randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(60.f, 60.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::White);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(40.f, 40.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
	case 3:
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 4:
		this->enemy.setSize(sf::Vector2f(20.f, 20.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;
	default:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;
	}

	

	//spawn the enemy
	this->enemies.push_back(this->enemy);
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
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void game::updateText()
{
	std::stringstream ss;

	ss << "Point: " << this->points;
	this->uiText.setString(ss.str());
}

void game::updateEnemies()
{
	/**
		@return void

		updatre the enemy spawn timer and spawns enemies
		when the total amout of enemies is smaller than the maximu.
		move enemies down
		remove the enemies at the adge of the screen
	*/
	//updating the timer for enemy spawing
	if (this->enemies.size() < this->maxEnemies) {
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

	//move nad update enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 3.f);

		//if the enemy is part the bottom of the scene
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);
			health--;
			std::cout << "Health: " << this->health << "\n";
		}

	}


	//check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					
					//gain points
					this->points += 1.f;
					if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::White)
						this->points += 15;
					else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
						this->points += 20;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 25;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 30;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 5;
					std::cout << "Points: " << this->points << "\n";

					//delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

				}
			}
		}

	}
	else
	{
		this->mouseHeld = false;
	}
}
void game::update()
{
	this->pollEvents();

	if(this->endGame==false)
	{
		this->updateMousePosition();

		this->updateText();

		this->updateEnemies();
	}

	//end game condition
	if (this->health <= 0) {
		this->endGame = true;
	}
}



void game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void game::renderEnemies(sf::RenderTarget& target)
{
	//rendering all the enemies
	for (auto& e : this->enemies) {
		this->window->draw(e);
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
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();

}
