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
		0.08, { 0, 76 }, 3),
	speaker(font, {30, winC::size.y - 232}, 32),
	d_text(font, {70, winC::size.y - 180}, 30)
//d_system("assets/dialogs/dialog_struct.json"),
//a_system("assets/asset_struct.json")
{
	char_left_2.loadFromFile("assets/images/characters/none_char.png");
	char_left_1.loadFromFile("assets/images/characters/none_char.png");
	char_right_1.loadFromFile("assets/images/characters/none_char.png");
	char_right_2.loadFromFile("assets/images/characters/none_char.png");


	speaker.setText(L"SomeName");
	d_text.setText(L"qweRTYUIOPASDFGHJKLZXCVBnmfghjVBNhjkUIO");
	dialogUI.loadFromFile("assets/images/UI/dialog.png");
	d_scale = winC::size.x / dialogUI.getSize().x;
	d_pos = {0, winC::size.y - dialogUI.getSize().y * d_scale };

}

game::states gameLogic::run(GUI::window* window) {
	while (true) {

		sf::Event event;

		while (window->getRenderWindow().pollEvent(event)) {
			window->update(event);
			red_button.update(event);
			menu_button.update(event);
			exit.update(event);
			handleKeyboard(event);
		}
		if (loadScene)
			createNewScene();

		drawUI(window);
		red_button.isClicked();
		if (menu_button.isClicked())
			return states::menu;
		else if (exit.isClicked() || window->isDone())
			return states::exit;


	}
}

void gameLogic::drawUI(GUI::window* window) {
	window->beginDraw();
	red_button.draw(window);
	menu_button.draw(window);
	exit.draw(window);
	auto sprite = sf::Sprite();
	sprite.setPosition(d_pos);
	sprite.setScale({ d_scale, d_scale });
	sprite.setTexture(dialogUI);
	window->getRenderWindow().draw(sprite);
	speaker.draw(window);
	d_text.draw(window);
	window->endDraw();
}


void gameLogic::createNewScene() {
	loadScene = false;
}

void gameLogic::handleKeyboard(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !flag) {
		flag = true;
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space && flag) {
		flag = false;
		loadScene = true;
	}
}