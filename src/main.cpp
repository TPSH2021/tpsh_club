#include "gameModule/gameSystem.h"

using namespace game;
using namespace gameModule;

int main() {
	// Program entry point.   
	Game game;
	//game.m_window.setFramerateLimit(60);
	// Creating our game object.    
	while (!game.GetWindow()->IsDone()) {
		// Game loop. 
		game.HandleInput();

		game.Update();
		game.Render();
	}


}