#pragma once

#include <memory>
#include <string>
#include <map>
#include <json.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace game {
	namespace assetsModule {
		class background {
		public:
			background(const int& ids, const nlohmann::json& structfile);
			const sf::Texture& getTexture();
		private:
			std::string id;
			sf::Texture img;
		};

		class character {
		public:
			character(const int& ids, const nlohmann::json& structfile);
			const sf::Texture& getEmotionById(std::string id);
			const std::vector<std::string>& getAllEmotions();
		private:
			std::string id;
			std::map<std::string, sf::Texture> emotions;
		};

		class assetsSystem {
		public:
			assetsSystem();
			const background& getBackground(std::string&);
			const character& getCharacter(std::string&);
			const std::wstring& getText(std::string&);

		private:
			std::map<std::string, background> backgrounds;
			std::map<std::string, character> characters;
			std::map<std::string, std::wstring> texts;
		};
	}  // namespace assetsModule
}  // namespace game