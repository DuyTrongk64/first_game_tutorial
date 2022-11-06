#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

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
	sf::Vector2f mousePosView;

	//resoure
	sf::Font font;

	//text
	sf::Text uiText;

	//game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//game object
	std::vector<sf::RectangleShape>enemies;
	sf::RectangleShape enemy;

	//private functions
	void initVariables();
	void initFonts();
	void initText();
	void initWindow();
	void initEnemies();

public:
	//constructor / destructors
	game();
	virtual ~game();

	//accessors
	const bool  running() const;
	const bool getEndGame() const;
	//functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePosition();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
	
};

