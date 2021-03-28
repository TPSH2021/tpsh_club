#include "assetsSystem.h"
#include <map>
#include <string>
#include <json.hpp>
#include <fstream>

using namespace game::assetsModule;

background::background(const int& ids, const std::string& filepath) : id(id) {
	std::ifstream jsonstream(filepath);
	nlohmann::json structfile;
	jsonstream >> structfile;
	id = structfile["bakgrounds_data"][ids]["id"];
	img.loadFromFile(structfile["backgrounds_data"][ids]["filename"]);
}

character::character(const int& ids, const std::string& filepath) {
	std::ifstream jsonstream(filepath);
	nlohmann::json structfile;
	jsonstream >> structfile;
	id = structfile["characters_data"][ids]["id"];
	std::vector<std::string> emotion = { "happy", "sad", "angry", "calm",  "smiling", "neutral" };
	for (int i = 0; i < emotion.size(); i++)
	{
		sf::Texture texture;
		texture.loadFromFile(structfile["characters_data"][ids][emotion[i] + "_emotion"]);
		emotions.insert(std::make_pair(emotion[i], texture));
	}
}

assetsSystem::assetsSystem(const std::string& filepath) {
	std::fstream jsonstream(filepath);
	nlohmann::json structfile;
	jsonstream >> structfile;
	for (int i = 0; i < structfile["bg_data"].size(); i++)
		backgrounds.insert(std::make_pair(structfile["bg_data"][i]["id"], background(i, filepath)));
	for (int i = 0; i < structfile["characters_data"].size(); i++)
		characters.insert(std::make_pair(structfile["characters_data"][i]["id"], character(structfile["characters_data"][i]["id"], filepath)));
}