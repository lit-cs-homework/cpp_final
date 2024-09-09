
#pragma once
#include "./backup.h"
#include "./map.h"

class GameConfig{
public:
  int difficulty;
  int coins;

  int stage;
  int life;

  Map& map;
  GameConfig(Map&);
};
