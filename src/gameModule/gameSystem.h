#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include "guiModule/gui.h"
#include "dialogModule/dialogSystem.h"
#include "assetsModule/assetsSystem.h"

namespace game {
	using namespace dialogModule;
	using namespace assetsModule;
	namespace gameModule {
		class gameLogic {
		public:
			gameLogic();
			void run(GUI::window* window);
		private:
			dialogSystem d_system;
			assetsSystem a_system;
		};
	}  // namespace gameModule
}  // namespace game