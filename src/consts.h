#pragma once
#include <SFML/System/Vector2.hpp>

namespace winC {
	const sf::Vector2f size = { 1920, 1080 };
}
namespace game {
	const enum class states {
		menu,
		game,
		exit,
	};
	const sf::Vector2f char_size = { 420, 746 };
	
}