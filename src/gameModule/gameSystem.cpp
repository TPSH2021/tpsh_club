#include "gameSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

using namespace game::gameModule;





gameLogic::gameLogic(const sf::Font& font) :
	red_button("assets/images/UI/redactor_c.png",
		"assets/images/UI/redactor_t.png",
		"assets/images/UI/redactor_a.png",
		0.08, { 0, 0 }, 1),
	menu_button("assets/images/UI/menu_c.png",
		"assets/images/UI/menu_t.png",
		"assets/images/UI/menu_a.png",
		0.08, { 0, 38 }, 2),
	exit("assets/images/UI/exit_c.png",
		"assets/images/UI/exit_t.png",
		"assets/images/UI/exit_a.png",
		0.08, { 0, 76 }, 3)
//d_system("assets/dialogs/dialog_struct.json"),
//a_system("assets/asset_struct.json")
{
	dialogUI.loadFromFile("assets/images/UI/dialog.png");
	d_scale = winC::size.x / dialogUI.getSize().x;
	d_pos = {0, winC::size.y - dialogUI.getSize().y * d_scale };
	// Setting up class members.
}

game::states gameLogic::run(GUI::window* window) {
	while (true) {
		window->beginDraw();
		sf::Event event;

		while (window->getRenderWindow().pollEvent(event)) {
			window->update(event);
			red_button.update(event);
			menu_button.update(event);
			exit.update(event);
		}
		red_button.draw(window);
		menu_button.draw(window);
		exit.draw(window);
		auto sprite = sf::Sprite();
		sprite.setPosition(d_pos);
		sprite.setScale({ d_scale, d_scale });
		sprite.setTexture(dialogUI);
		window->getRenderWindow().draw(sprite);

		red_button.isClicked();
		if (menu_button.isClicked())
			return states::menu;
		else if (exit.isClicked() || window->isDone())
			return states::exit;

		window->endDraw();
	}
}

void gameLogic::drawUI(GUI::window* window) {
	
}



