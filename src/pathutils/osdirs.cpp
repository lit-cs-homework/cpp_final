

#include "../../include/pathutils.h"
#include <string>
#include <cstring>

namespace Path
{

namespace Dir
{

#define RetXDGDATAOrJoin(p) \
    CCStr p__ = getenv("XDG_DATA_HOME");\
    if (NULL == p__) return joinPath(getenv("HOME"), stripPathEnd(p).c_str());\
    else return stripPathEnd(p__);

std::string Data()
{
# ifdef _WIN32
    CStr p = {getenv("APPDATA")};
    auto s = stripPathEnd(p);
    return s;
# elif __APPLE__
    RetXDGDATAOrJoin("Library/Application Support")
# else
    RetXDGDATAOrJoin(".local/share")
# endif
}
#undef RetXDGDATAOrJoin


const std::string&
Cwd(){
    static std::string res = ".";
    return res;
}

} // namespace Dir
  
} // namespace Path
