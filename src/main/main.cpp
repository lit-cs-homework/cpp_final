
#include "game.h"

int main(int argc, char* argv[])
{
  const char* backupDir = argv[1];
  if (backupDir == NULL)
    backupDir = ".";
  StartGame(backupDir);
}

