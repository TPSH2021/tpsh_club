#pragma once

#include <string>
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
namespace GUI {

	class window {
	public:
		window();
		window(const std::string& l_title, const sf::Vector2u& l_size);
		~window();
		void beginDraw();
		void endDraw();

		sf::Vector2u getWindowSize();
		sf::RenderWindow& getRenderWindow();
		bool isDone();
		void doDone(bool);
		bool isFullscreen();
		void update(const sf::Event& event);
		void toggleFullscreen();
		void destroy();
	private:
		void setup(const std::string& l_title, const sf::Vector2u& l_size);
		void create();
		sf::RenderWindow m_window;
		sf::Vector2u m_windowSize;
		std::string m_windowTitle;
		bool m_isDone;
		bool m_isFullscreen;
	};

	class label {
	public:
		label(const sf::Font& font, const sf::Vector2f& pos, int size);
		void setText(const std::wstring& text);
		void update(const sf::Event& event);
		void draw(window& window);
		void draw(window* window);
	private:
		sf::Text mText;
	};

	class button {
	public:
		enum class Type
		{
			Normal,
			Selected,
			Triggered,
			Pressed
		};

		button(const std::string&,
			const std::string&,
			const std::string&,
			float scale,
			const sf::Vector2f& pos);

		bool isClicked();
		void update(const sf::Event& event);
		void draw(window& window);
		void draw(window* window);
	private:
		void select();
		void deselect();
		void activate();
		void deactivate();
	private:

		float scale;
		sf::Vector2f g_scale;
		sf::Vector2f pos;
		sf::Texture common;
		sf::Texture triggered;
		sf::Texture clicked;

		bool isSelected;
		bool isActive;
		bool flag;
		Type state;
	};

	class textButton {
	public:
		textButton(const std::string&,
			const std::string&,
			const std::string&,
			float scale,
			const sf::Vector2f& pos,
			const sf::Font& font,
			int size
		);
		button btn;
		label lbl;
	};
	 
	class mBackground {
	public:
		mBackground(const std::string& path);
		void update(const sf::Event& event);
		void draw(window& window);
		void draw(window* window);
	private:
		sf::Vector2f g_scale;
		sf::Vector2f pos;
		sf::Texture texture;
		sf::Vector2f scale;
	};
	enum class buttonStyle {
		editor,
		menu,
		play,
		exit
	};

	button createNewButton(buttonStyle style, float scale, sf::Vector2f pos);
}