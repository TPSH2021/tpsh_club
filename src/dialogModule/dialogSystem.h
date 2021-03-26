#pragma once

#include <memory>
#include "assetsSystem.h"
#include <map>
#include <string>


namespace game {
    namespace dialogModule {

        class replica {
        public:
            std::string getBackgroundId();
            std::string getBackgroundId();

            std::pair<std::string, std::string> getLeft1Character();
            std::pair<std::string, std::string> getLeft2Character();
            std::pair<std::string, std::string> getRight1Character();
            std::pair<std::string, std::string> getRight2Character();

            void setBackgroundId(std::string id);

            void setLeft1Character(std::pair<std::string, std::string> id);
            void setLeft2Character(std::pair<std::string, std::string> id);
            void setRight1Character(std::pair<std::string, std::string> id);
            void setRight2Character(std::pair<std::string, std::string> id);
        private:
            std::string id;
            std::string background_id;
            std::pair<std::string, std::string> character_left2;
            std::pair<std::string, std::string> character_left1;
            std::pair<std::string, std::string> character_right1;
            std::pair<std::string, std::string> character_right2;
            std::string speaker;
            std::vector<std::pair<std::string, std::string>> jumps;
            std::string text;
        };


        class dialog {
        public:
            replica& getReplica();
            bool next();
        private:
            std::map<std::string, replica> replicas;
            std::string cur_replica;
            std::string id;
        };


        class dialogSystem {
        public:
            dialogSystem();
            dialog& getDialog();
            bool next();

            ~dialogSystem();
        private:
            std::map<std::string, dialog> dialogs;
            std::string cur_dialog;
        };
    }
}
x