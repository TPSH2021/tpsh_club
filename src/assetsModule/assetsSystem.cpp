#include "assetsSystem.h"
#include <map>
#include <string>
#include <json.hpp>
#include <fstream>

namespace game {
  namespace assetsModule {
    background::background(const std::string& id, const std::string& filepath) : id(id) {
      img.loadFromFile(filepath);
    }

    character::character(const std::string& id, const std::map<std::string, sf::Texture>& em) : id(id) {
      emotions = em;
    }

    assetsSystem::assetsSystem(const std::string& filepath) {
      std::fstream jsonstream(filepath);
      nlohmann::json structfile;
      jsonstream >> structfile;
      for (int i = 0; i < structfile["bg_data"].size(); i++) {
        background buff(structfile["bg_data"][i]["id"], structfile["bg_data"][i]["filename"]);
        backgrounds.insert(std::make_pair(structfile["bg_data"][i]["id"], buff));
      }
      for (int i = 0; i < structfile["characters_data"].size(); i++) {
        std::vector<std::string> emotions = { "happy", "sad", "angry", "calm",  "smiling", "neutral" };
        std::map<std::string, sf::Texture> cem;
        for (int r = 0; r < emotions.size(); r++) {
          sf::Texture emotion;
          emotion.loadFromFile(structfile["characters_data"][i][emotions[r] + "_emotion"]);
          cem.insert(std::make_pair(emotions[r], emotion));
        }
        character buff(structfile["characters_data"][i]["id"], cem);
        characters.insert(std::make_pair(structfile["characters_data"][i]["id"], buff));
      }
    }
  }  // namespace assetsModule
} // namespace game