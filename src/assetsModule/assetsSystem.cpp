#include "assetsSystem.h"
#include <map>
#include <string>
#include <json.hpp>
#include <fstream>
#include <iostream>

using namespace game::assetsModule;

background::background(const int& ids, const nlohmann::json& structfile) {
	id = structfile["bg_data"][ids]["id"];
	img.loadFromFile(structfile["bg_data"][ids]["file"]);
}

character::character(const int& ids, const nlohmann::json& structfile) {
	id = structfile["character_data"][ids]["id"];
	std::vector<std::string> emotion = { "happy", "sad", "angry", "calm",  "smiling", "neutral" };
	for (int i = 0; i < emotion.size(); i++)
	{
		sf::Texture texture;
		texture.loadFromFile(structfile["character_data"][ids][emotion[i]]);
		emotions.insert(std::make_pair(emotion[i], texture));
	}
}

assetsSystem::assetsSystem() {
	std::fstream jsonstream("assets/asset_struct.json"), localestream("assets/texts/locale.json");
	nlohmann::json structfile, locale;
	jsonstream >> structfile;
	localestream >> locale;
	for (int i = 0; i < structfile["bg_data"].size(); i++)
		backgrounds.insert(std::make_pair(structfile["bg_data"][i]["id"], background(i, structfile)));
	for (int i = 0; i < structfile["character_data"].size(); i++)
	{
		std::cout << structfile["character_data"][i]["id"] << std::endl;
		characters[structfile["character_data"][i]["id"]] = character(i, structfile);
	}
	for (int i = 0; i < locale.size(); i++)
		texts[locale[i]["id"]] = locale[i]["data"];
}



const sf::Texture& character::getEmotionById(std::string id) const {
	return emotions.at(id);
}

const std::vector<std::string>& character::getAllEmotions() {
	std::vector<std::string> res;
	for (const auto& c : emotions)
		res.push_back(c.first);
	return res;
}


const background& assetsSystem::getBackground(std::string& id) {
	return backgrounds.at(id);
}
const character& assetsSystem::getCharacter(std::string& id) {
	return characters.at(id);
}
const std::string& assetsSystem::getText(const std::string& id) {
	return texts.at(id);
}

const sf::Texture& background::getTexture() {
	return img;
}	