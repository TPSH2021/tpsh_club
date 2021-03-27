#pragma once
#include <memory>
#include <string>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace game {
	namespace assetsModule {


		class asset {
		public:
			const std::weak_ptr<sf::Image> getImage();
			asset(const std::string&);
		private:
			sf::Image img;
		};


		class background {
		public:
			sf::Sprite getSprite();
			
		private:
			std::string id;
			sf::Sprite img;
		};


		class character {
		public:
			sf::Sprite getEmotionById(std::string emotion);
			std::vector<std::string> getAllEmotions();
		private:
			std::string name;
			std::string id;
			std::map<std::string, asset> emotions;
		};


		class assetsSystem {
		public:
			 ~assetsSystem();
			 std::weak_ptr<background> getBackground(std::string&);
			 std::weak_ptr<character> getCharacter(std::string&);
		private:
			assetsSystem();
			std::map<std::string, background> backgrounds;
			std::map<std::string, character> characters;
		};
	}
}