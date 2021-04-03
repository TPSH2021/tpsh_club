#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include "guiModule/gui.h"
#include "dialogModule/dialogSystem.h"
#include "assetsModule/assetsSystem.h"
#include "guiModule/gui.h"
#include "consts.h"

namespace game {
	using namespace dialogModule;
	using namespace assetsModule;
	namespace gameModule {
		class gameLogic {
		public:
			gameLogic(const sf::Font& font, dialogSystem*, assetsSystem*);
			states run(GUI::window* window);
		private:
			GUI::editor editor;
			bool flag;
			bool is_editor_active;
			bool loadScene;
			void handleKeyboard(const sf::Event& event);
			void handleChsButtons(const sf::Event& event);
			void createNewScene(bool);
			void drawUI(GUI::window* window);
			float d_scale;
			bool endGame;
			sf::Vector2f d_pos;
			sf::Texture dialogUI;
			GUI::button red_button;
			GUI::button menu_button;
			GUI::button exit;
			GUI::label speaker;
			GUI::label d_text;
			sf::Font ffont;
			dialogSystem* d_system;
			assetsSystem* a_system;
			std::vector<GUI::textButton> choice_btns;
			int chs_jump;
		};
	}  // namespace gameModule
}  // namespace game