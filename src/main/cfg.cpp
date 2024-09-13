

#include "cfg.h"


GameConfig::GameConfig(Map& m, const std::string& backupDir): map(m)
{
    backup = std::make_shared<BackupWithTime>(backupDir);
}

bool
GameConfig::tryLoadBackup()
{
    return map.tryLoadBackup(*backup);
}
