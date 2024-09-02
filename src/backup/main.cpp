
#include "../../include/backup.h"
#include "../../lib/hps/hps.h"

#include <fstream>

std::string
Backup::getFilePath() {return std::string(dir) + filename;}

void Backup::setFileName(const std::string& p) {
    filename = p.c_str();
}

bool Backup::hasData() {
    std::ifstream in;
    in.open(getFilePath(), std::ios::ate|std::ios::binary);
    if(in.fail()) return false;
    auto res = in.tellg() != 0;
    in.close();
    return res;
}

Backup::Backup() {}

Backup Backup::Cwd() {
    return Backup();
}

