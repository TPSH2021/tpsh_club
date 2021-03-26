#pragma once
#include <memory>
#include <string>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
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
			const std::weak_ptr<asset> getBackground();
		private:
			std::string id;
            asset background;
		};


		class character {
		public:
			const std::weak_ptr<asset> getCharacterEmotion(std::string);
		private:
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
