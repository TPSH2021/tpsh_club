#include "menu.h"
#include "consts.h"
#include "guiModule/gui.h"
#include <SFML/Window/Event.hpp>
using namespace game;

using namespace menuModule;

menu::menu(const sf::Font& font) :
play("assets/images/UI/play.png", 1, { 100, 100 }, 1),
exit("assets/images/UI/exit.png", 1, { 100, 300 }, 2),
bg("assets/images/UI/bg.png"),
title(font, { 0, 0 }, 32)
{}

states menu::run(GUI::window* window) {
	while (true) {
		// State loop. 
		window->beginDraw();
		sf::Event event;
		//std::cout << window.getRenderWindow().getSize().x << std::endl;
		while (window->getRenderWindow().pollEvent(event)) {
			window->update(event);
			bg.update(event);
			play.update(event);
			exit.update(event);
		}
		bg.draw(window);
		title.draw(window);
		play.draw(window);
		exit.draw(window);
		if (play.isClicked())
			return states::game;
		else if (exit.isClicked())
			return states::exit;
		window->endDraw();
	}
	window->doDone(true);
	window->destroy();
}
