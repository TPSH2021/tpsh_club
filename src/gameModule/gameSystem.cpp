#include "gameSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>
#include "helper_func.hpp"
using namespace game::gameModule;

using namespace GUI;


gameLogic::gameLogic(const sf::Font& font, dialogSystem* d2_system, assetsSystem* a2_system) :
	red_button(createNewButton(buttonStyle::editor, 0.06, { 0, 0 })),
	menu_button(createNewButton(buttonStyle::menu, 0.06, { 0, 35 })),
	exit(createNewButton(buttonStyle::exit, 0.06, { 0, 70 })),
	speaker(font, { 30, winC::size.y - 232 }, 32),
	d_text(font, { 70, winC::size.y - 180 }, 30)
{
	d_system = d2_system;
	a_system = a2_system;
	is_editor_active = false;
	loadScene = false;
	ffont = font;
	speaker.setText(L"SomeName");
	d_text.setText(L"SomeText");
	dialogUI.loadFromFile("assets/images/UI/dialog.png");
	d_scale = winC::size.x / dialogUI.getSize().x;
	d_pos = { 0, winC::size.y - dialogUI.getSize().y * d_scale };
	createNewScene(false);
}

game::states gameLogic::run(GUI::window* window) {

	while (true) {

		sf::Event event;

		while (window->getRenderWindow().pollEvent(event)) {
			window->update(event);
			if(is_editor_active)
				ImGui::SFML::ProcessEvent(event);
			red_button.update(event);
			menu_button.update(event);
			exit.update(event);
			handleKeyboard(event);
			handleChsButtons(event);
		}
		if (loadScene) {
			std::cout << "loaded" << std::endl;
			createNewScene(true);
		}
		if (is_editor_active)
			editor.Update(window->getRenderWindow(), d_system, a_system);
		if (red_button.isClicked()) {
			if (is_editor_active) {
				is_editor_active = false;
				editor.ShutDown();
			}
			else {
				editor.Init(window->getRenderWindow());
				is_editor_active = true;
				editor.Update(window->getRenderWindow(), d_system, a_system);
			}
		}
		if (menu_button.isClicked())
			return states::menu;
		else if (exit.isClicked() || window->isDone())
			return states::exit;
		else if (endGame)
			return states::menu;

		drawUI(window);	


	}
}

void gameLogic::handleChsButtons(const sf::Event& event) {
	for (int i(0); i < choice_btns.size(); ++i) {
		choice_btns[i].btn.update(event);
		if (choice_btns[i].btn.isClicked()) {
			chs_jump = i;
			loadScene = true;
			return;
		}	
	}
}

void gameLogic::drawUI(GUI::window* window) {
	window->beginDraw();
	auto bg_sprite = sf::Sprite();
	bg_sprite.setTexture(a_system->getBackground(d_system->getDialog().getReplica().getBackgroundId()).getTexture());

	bg_sprite.setScale(
		{ winC::size.x / a_system->getBackground(d_system->getDialog().getReplica().getBackgroundId()).getTexture().getSize().x,
		 winC::size.y / a_system->getBackground(d_system->getDialog().getReplica().getBackgroundId()).getTexture().getSize().y });
	window->getRenderWindow().draw(bg_sprite);
	auto char_l_2_sprite = sf::Sprite();
	auto char_l_1_sprite = sf::Sprite();
	auto char_r_1_sprite = sf::Sprite();
	auto char_r_2_sprite = sf::Sprite();

	auto char_l_2 = d_system->getDialog().getReplica().getLeft2Character();
	auto char_l_1 = d_system->getDialog().getReplica().getLeft1Character();
	auto char_r_1 = d_system->getDialog().getReplica().getRight1Character();
	auto char_r_2 = d_system->getDialog().getReplica().getRight2Character();

	float k = winC::size.x / 4;

	if (char_l_2.first != "none" && char_l_2.second != "none") {
		char_l_2_sprite.setTexture(a_system->getCharacter(char_l_2.first).getEmotionById(char_l_2.second));
		float k_x = char_size.x / a_system->getCharacter(char_l_2.first).getEmotionById(char_l_2.second).getSize().x;
		float k_y = char_size.y / a_system->getCharacter(char_l_2.first).getEmotionById(char_l_2.second).getSize().y;
		char_l_2_sprite.setScale({ k_x, k_y});
		char_l_2_sprite.move({ 20, 100});
	}
	if (char_l_1.first != "none" && char_l_1.second != "none") {
		char_l_1_sprite.setTexture(a_system->getCharacter(char_l_1.first).getEmotionById(char_l_1.second));
		float k_x = char_size.x / a_system->getCharacter(char_l_1.first).getEmotionById(char_l_1.second).getSize().x;
		float k_y = char_size.y / a_system->getCharacter(char_l_1.first).getEmotionById(char_l_1.second).getSize().y;
		char_l_1_sprite.setScale({ k_x, k_y });
		char_l_1_sprite.move({ 20 + k, 100 });
	}
	if (char_r_1.first != "none" && char_r_1.second != "none") {
		char_r_1_sprite.setTexture(a_system->getCharacter(char_r_1.first).getEmotionById(char_r_1.second));
		float k_x = char_size.x / a_system->getCharacter(char_r_1.first).getEmotionById(char_r_1.second).getSize().x;
		float k_y = char_size.y / a_system->getCharacter(char_r_1.first).getEmotionById(char_r_1.second).getSize().y;
		char_r_1_sprite.setScale({ k_x, k_y });
		char_r_1_sprite.move({ winC::size.x - 20 - k - char_size.x, 100 });
	}
	if (char_r_2.first != "none" && char_r_2.second != "none") {
		char_r_2_sprite.setTexture(a_system->getCharacter(char_r_2.first).getEmotionById(char_r_2.second));
		float k_x = char_size.x / a_system->getCharacter(char_r_2.first).getEmotionById(char_r_2.second).getSize().x;
		float k_y = char_size.y / a_system->getCharacter(char_r_2.first).getEmotionById(char_r_2.second).getSize().y;
		char_r_2_sprite.setScale({ k_x, k_y });
		char_r_2_sprite.move({ winC::size.x - 20 - char_size.x, 100 });
	}
	window->getRenderWindow().draw(char_l_2_sprite);
	window->getRenderWindow().draw(char_l_1_sprite);
	window->getRenderWindow().draw(char_r_1_sprite);
	window->getRenderWindow().draw(char_r_2_sprite);

	red_button.draw(window);
	menu_button.draw(window);
	exit.draw(window);
	auto d_sprite = sf::Sprite();
	d_sprite.setPosition(d_pos);
	d_sprite.setScale({ d_scale, d_scale });
	d_sprite.setTexture(dialogUI);
	window->getRenderWindow().draw(d_sprite);

	speaker.draw(window);
	d_text.draw(window);

	for (auto& b : choice_btns)
	{
		b.btn.draw(window);
		b.lbl.draw(window);
	}
	if (is_editor_active)
		editor.Render(window->getRenderWindow());
	window->endDraw();
}


void gameLogic::createNewScene(bool need_next) {
	if (chs_jump != -1) {
		if (need_next && d_system->getDialog().getReplica().getJumps()[0].first.size() == 0)
			endGame = d_system->next(d_system->getDialog().getJump());
		else if (need_next && !endGame)
			d_system->getDialog().next(d_system->getDialog().getReplica().getJumps()[chs_jump].first);
		if (!endGame) {
			choice_btns.clear();
			if (d_system->getDialog().getReplica().getJumps().size() == 1)
				chs_jump = 0;
			else {

				for (int i(0); i < d_system->getDialog().getReplica().getJumps().size(); ++i) {
					choice_btns.push_back(GUI::textButton(
						"assets/images/UI/choose_c.png",
						"assets/images/UI/choose_t.png",
						"assets/images/UI/choose_a.png",
						0.15,
						{ 200.0f, 100 + i * 70.0f }, ffont, 18));
					choice_btns[i].lbl.setText(utf8_to_utf16(a_system->getText(d_system->getDialog().getReplica().getJumps()[i].second)));
				}
				chs_jump = -1;
				std::cout << choice_btns.size() << std::endl;
			}
			speaker.setText(utf8_to_utf16(a_system->getText(d_system->getDialog().getReplica().getSpeaker())));
			d_text.setText(utf8_to_utf16(a_system->getText(d_system->getDialog().getReplica().getId())));
		}
	}
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
