#pragma once
#include<iostream>
#include<vector>
#include<ctime>

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

	//mouse position
	sf::Vector2i mousePosWindow;

	//game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;


	//game object
	std::vector<sf::RectangleShape>enemies;
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
	void spawnEnemy();

	void pollEvents();
	void update();
	void updateEnemies();
	void render();
	void renderEnemies();
	void updateMousePosition();
};

