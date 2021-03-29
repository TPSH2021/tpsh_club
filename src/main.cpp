#include "gameModule/gameSystem.h"
#include "guiModule/gui.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include "consts.h"
using namespace game;
using namespace gameModule;
using namespace GUI;




int main() {
	// Program entry point.   
	window window("game", sf::Vector2u(1280, 720));
	sf::Font stdFont;
	stdFont.loadFromFile("assets/ConsolasBold.ttf");
	label label(stdFont, {100, 100}, 32);
	button button("assets/images/UI/play.png",
		0.8,
		{100, 400},
		1);
	auto img = sf::Image();
	label.setText(L"лемч");
	while (!window.isDone()) {
		// State loop. 
		window.beginDraw();
		sf::Event event;
		//std::cout << window.getRenderWindow().getSize().x << std::endl;
		while (window.getRenderWindow().pollEvent(event)) {
			window.update(event);
			button.update(event);
		}
		label.draw(window);
		button.draw(window);
		window.endDraw();
	}


}