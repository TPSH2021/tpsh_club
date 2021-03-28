#pragma once

#include <string>
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
namespace GUI {

	class label {
	public:
		void setText(const std::string& text);
		void update(const sf::Event& event);
		const sf::Text& getDrawable() const;
	private:
		sf::Text mText;
	};

	class button {
	public:
		enum Type
		{
			Normal,
			Selected,
			Pressed
		};

		button(const std::string& text,
			const sf::Vector2u& size,
			const sf::Vector2u& pos);

		~button();
		bool isClicked() const;
		void update(const sf::Event& event);
		void draw(window window);
		void setId(uint8_t);
		uint8_t getId() const;
	private:
		void changeTexture(Type buttonType);
		void select();
		void deselect();
		void activate();
		void deactivate();
	private:
		uint8_t id;
		sf::Sprite mSprite;
		label mLabel;
		bool mIsSelected;
		bool mIsActive;
	};

	class window {
	public:
		window();
		window(const std::string& l_title, const sf::Vector2u& l_size);
		~window();
		void beginDraw();  // Clear the window.
		void endDraw();    // Display the changes.

		sf::Vector2u getWindowSize();
		sf::RenderWindow& getRenderWindow();
		bool isDone();
		bool isFullscreen();
		void update();
		void toggleFullscreen();
	private:
		void setup(const std::string& l_title, const sf::Vector2u& l_size);
		void destroy();
		void create();
		sf::RenderWindow m_window;
		sf::Vector2u m_windowSize;
		std::string m_windowTitle;
		bool m_isDone;
		bool m_isFullscreen;
	}; 


}