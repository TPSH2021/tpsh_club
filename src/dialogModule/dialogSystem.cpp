#include "dialogSystem.h"
#include <fstream>
#include <json.hpp>
#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <iostream>

using namespace game::dialogModule;

//-------------------------------------------------------------------replica
replica::replica(const int& ids, const std::string& filepath) {
	std::ifstream jsonstream(filepath);
	nlohmann::json structure;
	jsonstream >> structure;
	id = structure["textPoints"][ids]["id"];
	background_id = structure["textPoints"][ids]["background"];
	speaker = structure["textPoints"][ids]["character"];
	character_left1 = { structure["textPoints"][ids]["left1"]["character"], structure["textPoints"][ids]["left1"]["emotion"] };
	character_left2 = { structure["textPoints"][ids]["left2"]["character"], structure["textPoints"][ids]["left2"]["emotion"] };
	character_right1 = { structure["textPoints"][ids]["right1"]["character"], structure["textPoints"][ids]["right1"]["emotion"] };
	character_right2 = { structure["textPoints"][ids]["right2"]["character"], structure["textPoints"][ids]["right2"]["emotion"] };
	for (int i = 0; i < structure["textPoints"][ids]["jumps"].size(); i++)
		jumps.push_back({ structure["textPoints"][ids]["jumps"][i]["nextPoint"], structure["textPoints"][ids]["jumps"][i]["description"] });
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
	character_left2 = id;
}

const std::pair<std::string, std::string>& replica::getLeft2Character() const {
	return character_left2;
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

const std::string& replica::getId() const {
	return id;
}

const std::string& replica::getSpeaker() const {
	return speaker;
}

const std::vector<std::pair<std::string, std::string>>& replica::getJumps() const {
	return  jumps;
}

//-------------------------------------------------------------------dialog
dialog::dialog(const std::string& id, const std::string& filepath, const std::string& jump) : id(id) {
	std::ifstream jsonstream(filepath);
	nlohmann::json structfile;
	jsonstream >> structfile;
	cur_replica = structfile["startPoint"];
	start_point = cur_replica;
	jump_to = jump;
	for (int i = 0; i < structfile["textPoints"].size(); i++)
		replicas.insert(std::make_pair( structfile["textPoints"][i]["id"], replica(i, filepath)));
}

replica& dialog::getReplica() {
	return replicas.at(cur_replica);
}

bool dialog::next(const std::string& replicaId) {
	cur_replica = replicaId;
	return true;
}

const std::string& dialog::getJump() {
	return jump_to;
}

void dialog::reset() {
	cur_replica = start_point;
}
//-------------------------------------------------------------------dialogSystem
dialogSystem::dialogSystem(const std::string& filepath) {
	auto cwd = std::filesystem::current_path().string();
	std::cout << cwd << std::endl;
	std::ifstream jsonstream;
	jsonstream.open(filepath, std::fstream::in);
	nlohmann::json structfile;
	jsonstream >> structfile;
	cur_dialog = structfile["start_point"];
	start_point = cur_dialog;
	for (int i = 0; i < structfile["data"].size(); i++)
		dialogs.insert(std::make_pair(structfile["data"][i]["id"], dialog(structfile["data"][i]["id"], structfile["data"][i]["dirname"], structfile["data"][i]["jump_to"])));
}

dialog& dialogSystem::getDialog() {
	if (cur_dialog == "")
		cur_dialog = start_point;
	return dialogs.at(cur_dialog);
}

bool dialogSystem::next(const std::string& dialogId) {
	dialogs.at(cur_dialog).reset();
	cur_dialog = dialogId;
	return dialogId == "";
}
