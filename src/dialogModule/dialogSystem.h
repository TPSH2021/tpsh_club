#pragma once

#include <memory>
#include "assetsModule/assetsSystem.h"
#include <map>
#include <string>
#include <vector>


namespace game {
	namespace dialogModule {

		class replica {
		public:
			replica(const int& id, const std::string& filepath);
			void setBackgroundId(const std::string& id);
			const std::string& getBackgroundId() const;

			void setLeft1Character(const std::pair<std::string, std::string>& id);
			const std::pair<std::string, std::string>& getLeft1Character() const;

			void setLeft2Character(const std::pair<std::string, std::string>& id);
			const std::pair<std::string, std::string>& getLeft2Character() const;

			void setRight1Character(const std::pair<std::string, std::string>& id);
			const std::pair<std::string, std::string>& getRight1Character() const;

			void setRight2Character(const std::pair<std::string, std::string>& id);
			const std::pair<std::string, std::string>& getRight2Character() const;

			const std::string& getId() const;
			const std::string& getSpeaker() const;
			const std::vector<std::pair<std::string, std::string>>& getJumps() const;
		private:
			std::string id;
			std::string background_id;
			std::pair<std::string, std::string> character_left1;
			std::pair<std::string, std::string> character_left2;
			std::pair<std::string, std::string> character_right1;
			std::pair<std::string, std::string> character_right2;
			std::string speaker;
			std::vector<std::pair<std::string, std::string>> jumps;
			std::string text;
		};

		class dialog {
		public:
			dialog(const std::string& id, const std::string& filepath, const std::string& jump);
			replica& getReplica();
			bool next(const std::string&);
			const std::string& getJump();
			void reset();
			std::string getCurReplica();
		private:
			std::map<std::string, replica> replicas;
			std::string cur_replica;
			std::string start_point;
			std::string id;
			std::string jump_to;
		};

		class dialogSystem {
		public:
			dialogSystem(const std::string& filepath);
			dialog& getDialog();
			bool next(const std::string&);
			std::string getCurDialog();
		private:
			std::map<std::string, dialog> dialogs;
			std::string cur_dialog;
			std::string start_point;
		};
	}  // namespace dialogModule
}  // namespace game