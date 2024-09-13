
#include "../../include/backup.h"
#include "../../lib/hps/hps.h"
#include <ctime>

#include <fstream>
#include <cstdio>

using CCStr = const char* const;
using CStr = const char*;


Backup::Backup(const char* const d) {
    dir = Path::normalizePathEnd(d);
}


Backup::Backup(const std::string& d) {
    dir = Path::normalizePathEnd(d.c_str());
}

std::string
Backup::getFilePath() const {return dir + stem + suffix;}

void Backup::setFileName(const std::string& p)
{
    auto pair = Path::splitExt(p.c_str());
    stem = pair.first;
    suffix = pair.second;
}

bool Backup::hasData() const {
    std::ifstream in;
    in.open(getFilePath(), std::ios::ate|std::ios::binary);
    if(in.fail()) return false;
    auto res = in.tellg() != 0;
    in.close();
    return res;
}

Backup::Backup() {}
Backup::~Backup(){}

// Backup Backup::Cwd() {
//     return Backup(".");
// }

// Backup Backup::inDataDir() {
//     return Backup(Path::Dir::Data());
// }
std::string
Backup::getAdditionalInfo() const {return "";}

bool Backup::del() {
    bool res = hasData();
    remove(getFilePath().c_str());
    return res;
}

static const size_t initSize = 10;
static_assert (initSize>0);

static const size_t threshold = 10;
#define largen() timefBuf.resize(timefBuf.size()*2)

#include <math.h>
static constexpr size_t thresholdLen =
    initSize * (2 << threshold);


TimeTFormatter::TimeTFormatter(const char* const s)
{
    if (s == NULL || s == "") {
        throw std::invalid_argument("bad format_str, NULL or \"\" given");
    }

    format_str = s;
    timefBuf.resize(initSize);
}

std::string&
TimeTFormatter::format(std::string& res, time_t t)
{
    size_t size;

    for ( size_t i = 0;
        (size = strftime(timefBuf.data(), timefBuf.size(),
            format_str,
            localtime(&t))
        ) == 0; i++
    ) {
        if (i > threshold) {
            if (timefBuf.size()<thresholdLen)
                return res; // may be some format that produces empty str are given, like `%p`
            //throw std::invalid_argument("bad format")
        }
        largen();
    }

    res.append(timefBuf, 0, size);

    return res;
}

void
BackupWithTime::setTimeFormat(const char* const format)
{
    if (ttfmt == nullptr) delete ttfmt;
    ttfmt = new TimeTFormatter(format);
}

BackupWithTime::BackupWithTime(const std::string& d): Backup(d)
{
    setTimeFormat();
}

BackupWithTime::~BackupWithTime() {
    delete ttfmt;
}

std::string
BackupWithTime::lastWriteTimeStr() const {
    std::string res;
    time_t t;
    try{
        t = Path::info::timet::lastModification(getFilePath().c_str());
    } catch (std::system_error e) {
        return cannotGetWriteTimeFallBackMsg;
    }
    ttfmt->format(res, t);
    return res;
}


std::string
BackupWithTime::getAdditionalInfo() const
{
    return lastWriteTimeStr();
}
