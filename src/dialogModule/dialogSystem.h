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
            std::pair<std::string, std::string> getLeft2Character();
        };


        class dialog {
        public:
        private:
            std::map<std::string, replica> replicas;
            std::string cur_replica;
        };



        class dialogSystem {
        public:
            dialog& getDialog(const std::string& id);
            ~dialogSystem();
            dialogSystem();
        private:
            std::map<std::string, dialog> dialogs;
            std::string cur_dialog;
        };
    }
}
