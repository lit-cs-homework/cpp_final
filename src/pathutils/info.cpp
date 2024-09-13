
#include "../../include/pathutils.h"



#ifdef _WIN32
#include <windows.h>
static inline
int64_t rdFileTime(FILETIME f) {
    return f.dwLowDateTime | f.dwHighDateTime << 32;
}
static const int64_t epochDiff = 116444736000000000;
static const auto hnsecsPerSec = 10000000;  // 10^7

static
time_t
toEpoch(FILETIME f){
    const auto win = rdFileTime(f);
    return (win - epochDiff) / hnsecsPerSec;
}

time_t
Path::info::timet::lastModification(CCStr file)
{
    WIN32_FIND_DATA f;
    auto h = FindFirstFileA(file, &f);
    if (h == -1)
      oserr::raise(oserr::cur(), file);
    auto res = toEpoch(f.ftLastWriteTime);
    FindClose(h);
    return res;
}

#else
#include <sys/stat.h>

time_t
Path::info::timet::lastModification(CCStr file)
{
  static struct stat st;
  if (stat(file, &st) == -1)
    oserr::raise(oserr::cur(), file);
  return st.st_mtime;
}


#endif
