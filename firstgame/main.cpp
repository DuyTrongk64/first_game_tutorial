#include<iostream>
#include "game.h"

//using namespace sf;

int main() {
	//init game engine
	game game;

	// game loop
	while (game.running())
	{
		// Update
		game.update();
		//Render
		game.render();
	}
	
	//end application
	return 0;
}