#include "gameModule/gameSystem.h"
#include "guiModule/gui.h"
#include <iostream>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "consts.h"
#include "menuModule/menu.h"
using namespace game;
using namespace gameModule;
using namespace GUI;
using namespace menuModule;


sf::Font stdFont;


int main() {
	// Program entry point.   
	window window("game", sf::Vector2u(1280, 720));
	stdFont.loadFromFile("assets/ConsolasBold.ttf");
	states state = states::menu;
	label label(stdFont, {100, 100}, 32);
	mBackground bg("assets/images/UI/bg.png");
	button button("assets/images/UI/play.png",
		0.8,
		{100, 400},
		1);
	auto img = sf::Image();
	label.setText(L"лемч");
	while (state != states::exit) {
		switch (state)
		{
		case game::states::menu:
		{
			menu menu_g(stdFont);
			state = menu_g.run(&window);
		}
			break;
		case game::states::game:
			break;
		case game::states::redactor:
			break;
		}
	}


}