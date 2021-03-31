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
			gameLogic(const sf::Font& font);
			states run(GUI::window* window);
		private:
			bool flag;
			bool loadScene;
			void handleKeyboard(const sf::Event& event);
			void createNewScene();
			void drawUI(GUI::window* window);
			float d_scale;
			sf::Vector2f d_pos;
			sf::Texture dialogUI;
			GUI::button red_button;
			GUI::button menu_button;
			GUI::button exit;
			GUI::label speaker;
			GUI::label d_text;
			dialogSystem d_system;
			assetsSystem a_system;
		};
	}  // namespace gameModule
}  // namespace game