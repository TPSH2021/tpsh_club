#include "dialogSystem.h"

namespace game {
	namespace dialogModule {
//-------------------------------------------------------------------replica
		void replica::setBackgroundId(const std::string& id) { background_id = id; }
		const std::string& replica::getBackgroundId() { return background_id; }

		void replica::setLeft1Character(
			const std::pair<std::string, std::string>& id) {
			character_left1 = id;
		}
		const std::pair<std::string, std::string>&
			replica::getLeft1Character() {
			return character_left1;
		}

		void replica::setLeft2Character(const std::pair<std::string, std::string>& id) {
			character_left1 = id;
		}
		const std::pair<std::string, std::string>&
			replica::getLeft2Character() {
			return character_left1;
		}

		void replica::setRight1Character(
			const std::pair<std::string, std::string>& id) {
			character_right1 = id;
		}
		const std::pair<std::string, std::string>&
			replica::getRight1Character() {
			return character_right1;
		}

		void replica::setRight2Character(
			const std::pair<std::string, std::string>& id) {
			character_right2 = id;
		}
		const std::pair<std::string, std::string>&
			replica::getRight2Character() {
			return character_right2;
		}

		const std::string& replica::getText() { return text; }
		const std::string& replica::getSpeaker() { return speaker; }
		const std::vector<std::pair<std::string, std::string>>& replica::getJumps() {
			return  jumps;
		}

		//-------------------------------------------------------------------dialog
		replica& dialog::getReplica() { return replicas.at(cur_replica); }
		bool dialog::next(const std::string& replicaId) {
			cur_replica = replicaId;
		}

		//-------------------------------------------------------------------dialogSystem
		dialog& dialogSystem::getDialog() {
			return dialogs.at(cur_dialog);
		}
		bool dialogSystem::next(const std::string& dialogId) {
			cur_dialog = dialogId;
		}

	}  // namespace dialogModule
}  // namespace game

