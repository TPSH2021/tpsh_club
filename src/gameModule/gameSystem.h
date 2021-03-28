#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include "guiModule/gui.h"

namespace game {
	namespace gameModule {
		

		class gameLogic {
		public:
			gameLogic();
			~gameLogic();
			void handleInput();
			void update();
			void render();

		private:
			std::shared_ptr<GUI::window> m_window;
		};
	}  // namespace gameModule
}  // namespace game