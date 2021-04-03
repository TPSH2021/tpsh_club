#include "gui.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <string>
#include <vector>
#include <assetsModule/assetsSystem.h>
#include <SFML/System/String.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Font.hpp>
#include "consts.h"
using namespace GUI;
using namespace game::dialogModule;
using namespace game::assetsModule;
//---------------------------------------------------------------label

label::label(const sf::Font& font, const sf::Vector2f& pos, int size) {
	mText = sf::Text(L"", font, size);
	mText.setPosition(pos);
	mText.setFillColor(sf::Color::Black);
}

void label::setText(const std::wstring& text) {
	std::vector<size_t> repl, tmp;
	std::wstring res(text);
	size_t d = 0;
	size_t l = 0;
	for (size_t i(0); i < text.size(); ++i)
		if (res[i] == L' ')
			tmp.push_back(i);
	for (auto& k : tmp) {
		if ((k - d >= 60 && k - d <= 65)) {
			repl.push_back(k);
			d = k;
			l = k;
		}
		else if (k - d > 65) {
			repl.push_back(l);
			d = l;
			l = k;
		}
		else {
			l = k;
		}
	}
	for (size_t i : repl)
		res[i] = L'\n';
	mText.setString(res);
}

void label::draw(window& window) {
	window.getRenderWindow().draw(mText);
}
void label::draw(window* window) {
	window->getRenderWindow().draw(mText);
}

//---------------------------------------------------------------button
button::button(const std::string & common_tx,
	const std::string& triggered_tx,
	const std::string& clicked_tx,
	float scale_u,
	const sf::Vector2f& pos_u) {
	g_scale = { 1, 1 };
	scale = scale_u;
	state = Type::Normal;
	isActive = false;
	isSelected = false;
	pos = pos_u;
	common.loadFromFile(common_tx);
	triggered.loadFromFile(triggered_tx);
	clicked.loadFromFile(clicked_tx);
	flag = false;
}

bool GUI::button::isClicked()
{
	if (state == Type::Pressed) {
		deactivate();
		return true;
	} 
	return false;
}

void button::draw(window& window) {
	auto sprite = sf::Sprite();
	sprite.setPosition(pos);
	sprite.setScale({ scale, scale });
	switch (state)
	{
	case GUI::button::Type::Normal:
		sprite.setTexture(common);
		break;
	case GUI::button::Type::Selected:
		sprite.setTexture(triggered);
		break;
	case GUI::button::Type::Triggered:
		sprite.setTexture(clicked);
		break;
	case GUI::button::Type::Pressed:
		sprite.setTexture(clicked);
		break;
	}
	window.getRenderWindow().draw(sprite);
}
void button::draw(window* window) {
	auto sprite = sf::Sprite();
	sprite.setPosition(pos);
	sprite.setScale({ scale, scale });
	switch (state)
	{
	case GUI::button::Type::Normal:
		sprite.setTexture(common);
		break;
	case GUI::button::Type::Selected:
		sprite.setTexture(triggered);
		break;
	case GUI::button::Type::Triggered:
		sprite.setTexture(clicked);
		break;
	case GUI::button::Type::Pressed:
		sprite.setTexture(clicked);
		break;
	}
	window->getRenderWindow().draw(sprite);
}

void button::update(const sf::Event& event) {
	if (event.type == sf::Event::EventType::MouseMoved) {
		auto m_pos = event.mouseMove;
		bool x_collide;
		bool y_collide;

		x_collide = ((pos.x * g_scale.x) <= m_pos.x && m_pos.x <= (pos.x + common.getSize().x * scale) * g_scale.x);
		y_collide = ((pos.y * g_scale.y) <= m_pos.y && m_pos.y <= (pos.y + common.getSize().y * scale) * g_scale.y);
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
		state = Type::Triggered;
	}
	else if (event.type == sf::Event::MouseButtonReleased && isSelected) {
		flag = false;
		activate();
	}
}

void button::select() {
	isSelected = true;
	if (state != Type::Pressed)
		state = Type::Selected;
}

void button::deselect() {
	isSelected = false;
	if (state != Type::Pressed)
		state = Type::Normal;
}

void button::activate() {
	isActive = true;
	state = Type::Pressed;
}

void button::deactivate() {
	isActive = false;
	state = Type::Selected;
}

textButton::textButton(const std::string& common_tx,
	const std::string& triggered_tx,
	const std::string& clicked_tx,
	float scale,
	const sf::Vector2f& pos,
	const sf::Font& font,
	int size) : btn(common_tx, triggered_tx, clicked_tx, scale, pos),
	lbl(font, { pos.x + 20, pos.y + 5 }, size)
{}
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


mBackground::mBackground(const std::string& path) {
	texture = sf::Texture();
	pos = { 0, 0 };
	texture.loadFromFile(path);
	scale.x = winC::size.x / texture.getSize().x;
	scale.y = winC::size.y / texture.getSize().y;
	g_scale = { 1, 1 };
}

void mBackground::update(const sf::Event& event) {
	if (event.type == sf::Event::Resized) {
		g_scale.x = event.size.width / winC::size.x;
		g_scale.y = event.size.height / winC::size.y;
	}
}


void mBackground::draw(window& window) {
	auto sprite = sf::Sprite();
	sprite.setPosition(pos);
	sprite.setScale(scale);
	sprite.setTexture(texture);
	window.getRenderWindow().draw(sprite);
}

void mBackground::draw(window* window) {
	auto sprite = sf::Sprite();
	sprite.setPosition(pos);
	sprite.setScale(scale);
	sprite.setTexture(texture);
	window->getRenderWindow().draw(sprite);
}

button GUI::createNewButton(buttonStyle style, float scale, sf::Vector2f pos)
{
	switch (style)
	{
	case GUI::buttonStyle::editor:
		return button("assets/images/UI/redactor_c.png",
			"assets/images/UI/redactor_t.png",
			"assets/images/UI/redactor_a.png",
			scale, pos
		);
	case GUI::buttonStyle::menu:
		return button("assets/images/UI/menu_c.png",
			"assets/images/UI/menu_t.png",
			"assets/images/UI/menu_a.png",
			scale, pos
		);
	case GUI::buttonStyle::play:
		return button("assets/images/UI/play_c.png",
			"assets/images/UI/play_t.png",
			"assets/images/UI/play_a.png",
			scale, pos
		);
	case GUI::buttonStyle::exit:
		return button("assets/images/UI/exit_c.png",
			"assets/images/UI/exit_t.png",
			"assets/images/UI/exit_a.png",
			scale, pos
		);
	}
}
//-----------------------------------------Editor

editor::editor()
{
	Mass = 100;
}

editor::~editor()
{}

void editor::Init(sf::RenderWindow& win) {
	ImGui::SFML::Init(win);
}

void editor::ProcessEvent(const sf::Event& event) {							
	ImGui::SFML::ProcessEvent(event);
}

void editor::Update(sf::RenderWindow& win, dialogSystem* dialogSystem, assetsSystem* assetsSystem) {
	ImGui::SFML::Update(win, deltaClock.restart());
	ImGui::Begin("Editor");
	ImGui::Text("Characters");
	std::vector<std::string> char_to_id;
	std::map<std::string, int> id_to_char{ {"none", 15} };
	int num = 0;
	const char* characters[128];
	for (auto& iter : assetsSystem->getAllCharacters()) {
		characters[num] = iter.first.c_str();
		char_to_id.push_back(iter.first);
		id_to_char[iter.first] = num++;
	}
	characters[num] = "none";
	char_to_id.push_back("none");
	auto key = dialogSystem->getDialog().getReplica().getLeft1Character();
	sel_left_1_char = id_to_char[key.first];
	sel_left_1_emot = em_to_id.at(key.second);
	ImGui::Combo("Central Left Character", &sel_left_1_char, characters, assetsSystem->getAllCharacters().size() + 1);
	ImGui::Combo("Central Left Emotions", &sel_left_1_emot, "happy\0sad\0angry\0calm\0smiling\0neutral\0none\0", 7);
	if (char_to_id[sel_left_1_char] != key.first || id_to_em[sel_left_1_emot] != key.second)
		dialogSystem->getDialog().getReplica().setLeft1Character({ char_to_id[sel_left_1_char], id_to_em[sel_left_1_emot] });

	
	key = dialogSystem->getDialog().getReplica().getLeft2Character();
	sel_left_2_char = id_to_char[key.first];
	sel_left_2_emot = em_to_id.at(key.second);
	ImGui::Combo("Outside Left Character", &sel_left_2_char, characters, assetsSystem->getAllCharacters().size() + 1);
	ImGui::Combo("Outside Left Emotions", &sel_left_2_emot, "happy\0sad\0angry\0calm\0smiling\0neutral\0none\0", 7);
	if (char_to_id[sel_left_2_char] != key.first || id_to_em[sel_left_2_emot] != key.second)
		dialogSystem->getDialog().getReplica().setLeft2Character({ char_to_id[sel_left_2_char], id_to_em[sel_left_2_emot] });

	key = dialogSystem->getDialog().getReplica().getRight2Character();
	sel_right_2_char = id_to_char[key.first];
	sel_right_2_emot = em_to_id.at(key.second);
	ImGui::Combo("Outside Right Character", &sel_right_2_char, characters, assetsSystem->getAllCharacters().size() + 1);
	ImGui::Combo("Outside Right Emotions", &sel_right_2_emot, "happy\0sad\0angry\0calm\0smiling\0neutral\0none\0", 7);
	if (char_to_id[sel_right_2_char] != key.first || id_to_em[sel_right_2_emot] != key.second)
		dialogSystem->getDialog().getReplica().setLeft2Character({ char_to_id[sel_right_2_char], id_to_em[sel_right_2_emot] });

	key = dialogSystem->getDialog().getReplica().getRight1Character();
	sel_right_1_char = id_to_char[key.first];
	sel_right_1_emot = em_to_id.at(key.second);
	ImGui::Combo("Central Right Character", &sel_right_1_char, characters, assetsSystem->getAllCharacters().size() + 1);
	ImGui::Combo("Central Right Emotions", &sel_right_1_emot, "happy\0sad\0angry\0calm\0smiling\0neutral\0none\0", 7);
	if (char_to_id[sel_right_1_char] != key.first || id_to_em[sel_right_1_emot] != key.second)
		dialogSystem->getDialog().getReplica().setRight1Character({ char_to_id[sel_right_1_char], id_to_em[sel_right_1_emot] });

	
	ImGui::End();
}

void editor::Render(sf::RenderWindow& win) {
	ImGui::SFML::Render(win);
}

void editor::ShutDown() {
	ImGui::SFML::Shutdown();
}