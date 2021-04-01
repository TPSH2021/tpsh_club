#include "menu.h"
#include "consts.h"
#include "guiModule/gui.h"
#include <SFML/Window/Event.hpp>
using namespace game;

using namespace menuModule;
using namespace GUI;
menu::menu(const sf::Font& font) :
	play(createNewButton(buttonStyle::play, 0.2, { 100, 100 })),
	exit(createNewButton(buttonStyle::exit, 0.2, { 100, 300 })),
	bg("assets/images/UI/bg.png")
{}

states menu::run(GUI::window* window) {
	while (true) {
		window->beginDraw();
		sf::Event event;
		while (window->getRenderWindow().pollEvent(event)) {
			window->update(event);
			bg.update(event);
			play.update(event);
			exit.update(event);
		}
		bg.draw(window);
		play.draw(window);
		exit.draw(window);
		if (play.isClicked())
			return states::game;
		else if (exit.isClicked() || window->isDone())
			return states::exit;
		window->endDraw();
	}
}
