#include "game.h"

//private function
void game::initVariables()
{
	this->window = nullptr;
}

void game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;
	this->window = new sf::RenderWindow(this->videomode, "game 1", sf::Style::Titlebar | sf::Style::Close);
}

void game::initEnemies()
{
	//this->enemy.setPosition();
	this->enemy.setSize(sf::Vector2f(100.f,100.f));
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

void game::update()
{
	this->pollEvents();
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
	this->window->clear(sf::Color(255, 0, 0, 255));

	//draw game
	this->window->draw(this->enemy);
	this->window->display();
}
