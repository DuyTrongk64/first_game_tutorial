#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

/*
*	class that acts as the game engine.
*	wrapper class.
*/
class game
{
private:
	//variables
	// window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videomode;

	//game object
	
	sf::RectangleShape enemy;
	//private functions
	void initVariables();
	void initWindow();
	void initEnemies();

public:
	//constructor / destructors
	game();
	virtual ~game();

	//accessors
	const bool  running() const;


	//functions
	void pollEvents();
	void update();
	void render();

};

