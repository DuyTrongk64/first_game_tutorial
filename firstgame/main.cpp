#include<iostream>
#include "game.h"

//using namespace sf;

int main() {

	//init srand
	std::srand(static_cast<unsigned> (time(NULL)));
	//init game engine
	game game;

	// game loop
	while (game.running() && !game.getEndGame())
	{
		// Update
		game.update();
		//Render
		game.render();
	}
	
	//end application
	return 0;
}