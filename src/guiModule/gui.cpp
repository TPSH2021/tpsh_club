#include "gui.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <SFML/System/String.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Font.hpp>
#include "consts.h"
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
button::button(const std::string &sprite_path,
	float scale_u,
	const sf::Vector2f& pos_u,
	uint8_t id_u) {
	g_scale = { 1, 1 };
	scale = scale_u;
	pos = pos_u;
	texture = sf::Texture();
	texture.loadFromFile(sprite_path);
	id = id_u;
}

bool GUI::button::isClicked()
{
	if (state == Type::Pressed) {
		state = Type::Normal;
		return true;
	} 
	return false;
}

void button::draw(window& window) {
	auto sprite = sf::Sprite();
	sprite.setPosition(pos);
	sprite.setScale({ scale, scale });
	sprite.setTexture(texture);
	window.getRenderWindow().draw(sprite);
}

void button::update(const sf::Event& event) {
	if (event.type == sf::Event::EventType::MouseMoved) {
		auto m_pos = event.mouseMove;
		bool x_collide = ((pos.x * g_scale.x) <= m_pos.x && m_pos.x <= (pos.x + texture.getSize().x * scale) * g_scale.x);
		bool y_collide = ((pos.y * g_scale.y) <= m_pos.y && m_pos.y <= (pos.y + texture.getSize().y * scale) * g_scale.y);
		if (x_collide && y_collide)
			select();
		else
			deselect();
	} 
	else if (event.type == sf::Event::Resized) {
		g_scale.x = event.size.width / winC::size.x;
		g_scale.y = event.size.height / winC::size.y;
	}
	else if (event.type == sf::Event::MouseButtonPressed && isSelected && !flag) {
		flag = true;
		state = Type::Pressed;
	}
	else if (event.type == sf::Event::MouseButtonReleased && isSelected) {
		flag = false;
		state = Type::Selected;
	}
}

void button::select() {
	isSelected = true;
	state = Type::Selected;
}

void button::deselect() {
	isSelected = false;
	state = Type::Normal;
}

void button::activate() {
	isActive = true;
	state = Type::Pressed;
}

void button::deactivate() {
	isActive = false;
	state = Type::Normal;
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

void window::update(const sf::Event& event) {

	if (event.type == sf::Event::Closed) {
		m_isDone = true;
	}
	else if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::F5) {
		toggleFullscreen();
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
void window::doDone(bool f) {
	m_isDone = f;
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


