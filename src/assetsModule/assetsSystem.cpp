#include "assetsSystem.h"

namespace game {
	namespace assets {
		asset::asset(const std::string& path) {
			sf::Image buff;
			this->img.loadFromFile(path);
		}
	}
}