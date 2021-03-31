#include "assetsSystem.h"
#include <map>
#include <string>
#include <json.hpp>
#include <fstream>

using namespace game::assetsModule;

background::background(const int& ids, const nlohmann::json& structfile) {
	id = structfile["bakgrounds_data"][ids]["id"];
	img.loadFromFile(structfile["backgrounds_data"][ids]["filename"]);
}

character::character(const int& ids, const nlohmann::json& structfile) {
	id = structfile["characters_data"][ids]["id"];
	std::vector<std::string> emotion = { "happy", "sad", "angry", "calm",  "smiling", "neutral" };
	for (int i = 0; i < emotion.size(); i++)
	{
		sf::Texture texture;
		texture.loadFromFile(structfile["characters_data"][ids][emotion[i] + "_emotion"]);
		emotions.insert(std::make_pair(emotion[i], texture));
	}
}

assetsSystem::assetsSystem() {
	std::fstream jsonstream("assets\\assets_struct.json"), localestream("assets\\texts\\Locale.json");
	nlohmann::json structfile, locale;
	jsonstream >> structfile;
	localestream >> locale;
	for (int i = 0; i < structfile["bg_data"].size(); i++)
		backgrounds.insert(std::make_pair(structfile["bg_data"][i]["id"], background(i, structfile)));
	for (int i = 0; i < structfile["characters_data"].size(); i++)
		characters.insert(std::make_pair(structfile["characters_data"][i]["id"], character(structfile["characters_data"][i]["id"], structfile)));
	for (auto& el : locale.items())
		texts.insert(std::make_pair(el.key(), std::wstring(L"" + el.value())));
}



const sf::Texture& character::getEmotionById(std::string id) {
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
const std::wstring& assetsSystem::getText(std::string& id) {
	return texts.at(id);
}

const sf::Texture& background::getTexture() {
	return img;
}	