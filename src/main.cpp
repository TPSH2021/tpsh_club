#include "gameModule/gameSystem.h"
#include "guiModule/gui.h"
#include <sstream>
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
	sf::Font stdFont;
	stdFont.loadFromFile("assets/ConsolasBold.ttf");
	label label(stdFont, {100, 100}, 32);

	label.setText(L"лемч");
	//game.m_window.setFramerateLimit(60);
	// Creating our game object.    
	while (!window.isDone()) {
		// State loop. 
		window.beginDraw();
		window.update();
		label.draw(window);
		window.endDraw();
	}


}