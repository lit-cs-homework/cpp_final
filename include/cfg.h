
#pragma once
#include "./backup.h"
#include "./map.h"

class GameConfig{
public:
  int difficulty;
  int coins;

  int stage;
  int life;

  std::shared_ptr<Backup> backup;
  Map& map;
  GameConfig(Map&, const std::string& backupDir);
  bool tryLoadBackup();
};
