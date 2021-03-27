#pragma once
#include <memory>
#include <string>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace game {
namespace assetsModule {
class background {
 public:
  background();
  const sf::Sprite& getSprite();
 private:
  std::string id;
  sf::Sprite img;
};

class character {
 public:
  character();
  const sf::Sprite& getEmotionById(std::string emotion);
  const std::vector<std::string>& getAllEmotions();
 private:
  std::string name;
  std::string id;
  std::map<std::string, sf::Sprite> emotions;
};

class assetsSystem {
 public:
  assetsSystem();
  const background& getBackground(std::string&);
  const character& getCharacter(std::string&);

 private:
  std::map<std::string, background> backgrounds;
  std::map<std::string, character> characters;
};
}  // namespace assetsModule
}  // namespace game