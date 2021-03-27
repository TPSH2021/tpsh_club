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
  replica();
  void setBackgroundId(const std::string& id);
  const std::string& getBackgroundId();

  void setLeft1Character(const std::pair<std::string, std::string>& id);
  const std::pair<std::string, std::string>& getLeft1Character();

  void setLeft2Character(const std::pair<std::string, std::string>& id);
  const std::pair<std::string, std::string>& getLeft2Character();
  
  void setRight1Character(const std::pair<std::string, std::string>& id);
  const std::pair<std::string, std::string>& getRight1Character();
  
  void setRight2Character(const std::pair<std::string, std::string>& id);
  const std::pair<std::string, std::string>& getRight2Character();

  const std::string& getText();
  const std::string& getSpeaker();
  const std::vector<std::string, std::string>& getJumps();

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
  dialog();
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

 private:
  std::map<std::string, dialog> dialogs;
  std::string cur_dialog;
};
}  // namespace dialogModule
}  // namespace game