#pragma once

#include <string>
#include <map>
#include <dialogModule/dialogSystem.h>
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

	class editor {
	public:
		editor();
		~editor();
		void Init(sf::RenderWindow& win);
		void ProcessEvent(const sf::Event& event);
		void Update(sf::RenderWindow& win, game::dialogModule::dialogSystem& dialogSystem, game::assetsModule::assetsSystem& assetsSystem);
		void Render(sf::RenderWindow& win);
		void ShutDown();
	private:

		int sel_left_1_char;
		int sel_left_1_emot;
		int sel_left_2_char;
		int sel_left_2_emot;
		sf::Clock deltaClock;
		const std::map<std::string, int> em_sel_to_id = { {"happy", 0 }, { "sad", 1 }, {"angry", 2}, {"calm", 3}, {"smiling", 4}, {"neutral", 5} };
		std::vector<std::string> em_id_to_sel = { "happy","sad", "angry","calm","smiling","neutral" };
		float Mass;
	};
}
