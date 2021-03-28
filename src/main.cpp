#include "gameModule/gameSystem.h"
#include "guiModule/gui.h"
using namespace game;
using namespace gameModule;
using namespace GUI;

enum class states {
	MENU,
	GAME,

};

int main() {
	// Program entry point.   
	window window("game", sf::Vector2u(1280, 720));
	//game.m_window.setFramerateLimit(60);
	// Creating our game object.    
	while (!window.isDone()) {
		// State loop. 
		window.beginDraw();
		window.update();
		window.endDraw();
	}


}