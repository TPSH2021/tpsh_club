#pragma once
#include <memory>
#include <string>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
namespace game {
	namespace assets {

		class assetInterface {
		public:
			virtual const std::weak_ptr<sf::Image> getImage() = 0;
		};
		class asset : public assetInterface {
		public:
			asset(const std::string&);
			const std::weak_ptr<sf::Image> getImage();
		private:
			sf::Image img;
		};

		class backgroundInterface {
			virtual const std::weak_ptr<asset> getBackground() = 0;
		};
		class background : backgroundInterface {
		private:
			std::string id;
            asset background;
		};

		class characterInterface {
        public:
			virtual const std::weak_ptr<asset> getCharacterEmotion(std::string) = 0;
		};
		class character : characterInterface {
		private:
			std::string id;
			std::map<std::string, asset> emotions;
		};
	}

	namespace assetsModule {
		
		class assetsSystemInterface {
			virtual ~assetsSystemInterface() = 0;
			virtual std::weak_ptr<assets::background> getBackground(std::string&) = 0;
			virtual std::weak_ptr<assets::character> getCharacter(std::string&) = 0;
			virtual std::weak_ptr<assetsSystemInterface> getAssetsSystem() = 0;
		};

		class assetsSystem : assetsSystemInterface {
		public:
			std::weak_ptr<assets::background> getBackground(std::string& id);
			std::weak_ptr<assets::character> getCharacter(std::string& id);
			
			~assetsSystem();
		private:
			assetsSystem();
			std::map<std::string, assets::background> backgrounds;
			std::map<std::string, assets::character> characters;
		};
	}
}
