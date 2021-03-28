#include "dialogSystem.h"
#include <fstream>
#include <json.hpp>
#include <vector>
#include <string>
#include <map>

using namespace game::dialogModule;

//-------------------------------------------------------------------replica
replica::replica(const int& ids, const std::string& filepath) {
	std::ifstream jsonstream(filepath);
	nlohmann::json structure;
	jsonstream >> structure;
	id = structure["textPoints"][ids]["id"];
	background_id = structure["textPoints"][id]["background"];
	speaker = structure["textPoints"][id]["character"];
	character_left1 = { structure["textPoints"][id]["left1"]["character"], structure["textPoints"][id]["left1"]["emotion"] };
	character_left2 = { structure["textPoints"][id]["left2"]["character"], structure["textPoints"][id]["left2"]["emotion"] };
	character_right1 = { structure["textPoints"][id]["right1"]["character"], structure["textPoints"][id]["right1"]["emotion"] };
	character_right2 = { structure["textPoints"][id]["right2"]["character"], structure["textPoints"][id]["right2"]["emotion"] };
	for (int i = 0; i < structure["textPoints"][id]["jumps"].size(); i++)
		jumps.push_back({ structure["textPoints"][id]["jumps"][i]["nextPoint"], structure["textPoints"][id]["jumps"][i]["description"] });	
}

void replica::setBackgroundId(const std::string& id) {
	background_id = id;
}

const std::string& replica::getBackgroundId() const {
	return background_id;
}

void replica::setLeft1Character(
	const std::pair<std::string, std::string>& id) {
	character_left1 = id;
}

const std::pair<std::string, std::string>& replica::getLeft1Character() const {
	return character_left1;
}

void replica::setLeft2Character(const std::pair<std::string, std::string>& id) {
	character_left1 = id;
}

const std::pair<std::string, std::string>& replica::getLeft2Character() const {
	return character_left1;
}

void replica::setRight1Character(const std::pair<std::string, std::string>& id) {
	character_right1 = id;
}

const std::pair<std::string, std::string>& replica::getRight1Character() const {
	return character_right1;
}

void replica::setRight2Character(
	const std::pair<std::string, std::string>& id) {
	character_right2 = id;
}

const std::pair<std::string, std::string>& replica::getRight2Character() const {
	return character_right2;
}

const std::string& replica::getText() const {
	return text;
}

const std::string& replica::getSpeaker() const {
	return speaker;
}

const std::vector<std::pair<std::string, std::string>>& replica::getJumps() const {
	return  jumps;
}

//-------------------------------------------------------------------dialog
dialog::dialog(const std::string& id, const std::string& filepath) : id(id) {
	std::ifstream jsonstream("filepath");
	nlohmann::json structfile;
	jsonstream >> structfile;
	cur_replica = structfile["startPoint"];
	for (int i = 0; i < structfile["textPoints"].size(); i++)
		replicas.insert(std::make_pair( structfile["textPoints"][i]["id"], replica(i, filepath)));
}

replica& dialog::getReplica() {
	return replicas.at(cur_replica);
}

bool dialog::next(const std::string& replicaId) {
	//TODO: why this method return bool?!
	cur_replica = replicaId;
	return true;
}

//-------------------------------------------------------------------dialogSystem
dialogSystem::dialogSystem(const std::string& filepath)
{
	std::ifstream jsonstream(filepath);
	nlohmann::json structfile;
	jsonstream >> structfile;
	cur_dialog = structfile["start_point"];
	for (int i = 0; i < structfile["data"].size(); i++)
		dialogs.insert(std::make_pair(structfile["data"][i]["id"], dialog(structfile["data"][i]["id"], structfile["data"][i]["dirname"])));
}

dialog& dialogSystem::getDialog() {
	return dialogs.at(cur_dialog);
}

bool dialogSystem::next(const std::string& dialogId) {
	cur_dialog = dialogId;
	return true;
}
