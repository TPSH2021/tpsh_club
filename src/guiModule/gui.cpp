#include "gui.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <SFML/System/String.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Font.hpp>
using namespace GUI;


//---------------------------------------------------------------label

label::label(const sf::Font& font, const sf::Vector2f& pos, int size) {
	mText = sf::Text(L"", font, size);
	mText.setPosition(pos);
	mText.setFillColor(sf::Color::Black);
}

void label::setText(const std::wstring& text) {
	mText.setString(text);
}

void label::draw(window& window) {
	window.getRenderWindow().draw(mText);
}

//---------------------------------------------------------------button
//button::button(const std::string &text, const sf::Vector2u& size, const sf::Vector2u& pos) {
//}

void button::select() {
	mIsSelected = true;
}

void button::deselect() {
	mIsSelected = false;
}

void button::activate() {
	mIsActive = true;
}

void button::deactivate() {
	mIsActive = false;
}
//---------------------------------------------------------------window
window::window() {
	setup("Window", sf::Vector2u(640, 480));
}

window::window(const std::string& l_title, const sf::Vector2u& l_size) {
	setup(l_title, l_size);
}

window::~window() {
	destroy();
}

void window::setup(const std::string& l_title, const sf::Vector2u& l_size) {
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullscreen = false;
	m_isDone = false;
	create();
}

void window::create() {
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
}

void window::destroy() {
	m_window.close();
}

void window::update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F5) {
			toggleFullscreen();
		}
	}
}

void window::toggleFullscreen() {
	m_isFullscreen = !m_isFullscreen;
	destroy();
	create();
}


void window::beginDraw() {
	m_window.clear(sf::Color::White);
}

void window::endDraw() {
	m_window.display();
}

bool window::isDone() {
	return m_isDone;
}

bool window::isFullscreen() {
	return m_isFullscreen;
}

sf::Vector2u window::getWindowSize() {
	return m_windowSize;
}

sf::RenderWindow& window::getRenderWindow() {
	return m_window;
}
