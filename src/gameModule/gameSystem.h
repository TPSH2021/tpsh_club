#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>

namespace game {
	namespace gameModule {
		class Window {
		public:
			Window();
			Window(const std::string& l_title, const sf::Vector2u& l_size);
			~Window();
			void BeginDraw();  // Clear the window.
			void EndDraw();    // Display the changes.

			sf::Vector2u GetWindowSize();
			bool IsDone();
			bool IsFullscreen();
			void Update();
			void ToggleFullscreen();
			void Draw(sf::Drawable& l_drawable);

		private:
			void Setup(const std::string& l_title, const sf::Vector2u& l_size);
			void Destroy();
			void Create();
			sf::RenderWindow m_window;
			sf::Vector2u m_windowSize;
			std::string m_windowTitle;
			bool m_isDone;
			bool m_isFullscreen;
		};
		class Game {
		public:
			Game();
			~Game();
			void HandleInput();
			void Update();
			void Render();
			Window* GetWindow();

		private:
			Window m_window;
		};
	}  // namespace gameModule
}  // namespace game