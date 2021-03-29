#include "gameSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

using namespace game::gameModule;





void gameLogic::render() {
	m_window->beginDraw();  // Clear.
	//m_window.Draw(m_mushroom);
	m_window->endDraw();  // Display.
}

gameLogic::gameLogic() {
	// Setting up class members.
}

gameLogic::~gameLogic() {}

void gameLogic::handleInput() {}


