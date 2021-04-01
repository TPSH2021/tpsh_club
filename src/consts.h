#pragma once
#include <SFML/System/Vector2.hpp>

namespace winC {
	const sf::Vector2f size = { 1280, 720 };
}
namespace game {
	const enum class states {
		menu,
		game,
		exit,
		redactor
	};
	const sf::Vector2f char_size = { 280, 720 };
	
}