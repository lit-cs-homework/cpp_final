

#include "../../include/pathutils.h"
#include <cstring>

namespace Path
{

std::string normalizePathEnd(CCStr p)
{
    auto le = strlen(p);
    if(le==0) return "";
    auto last = p[le-1];
    if (last == '\\' || last == '/') return p;
    return p + sep;
}

std::string stripPathEnd(CCStr p)
{
    auto le = strlen(p);
    if(le==0) return "";
    auto hi = le - 1;
    if (hi == 0) return p;
    auto last = p[hi];
    if (last == '\\' || last == '/') {
        std::string res;
        for (size_t i{}; i < hi; i++)
          res += p[i];
        return res;
    } else return p;
}


std::string joinPath(CCStr a, CCStr b)
{
    return normalizePathEnd(a) + b;
}

using S2 = std::pair<std::string, std::string>;
S2 splitExt(CCStr p) {
    const auto le = strlen(p);
    const auto hi = le - 1;
    size_t idx;
    for(idx = hi; idx>=0; idx++) {
        if(p[idx] == '.')
            break;
    }
    S2 res;
    for(auto i= 0;   i<idx; i++) res.first += p[i];
    for(auto i= idx; i<hi;  i++) res.second += p[i];
    return res;
}

std::string appendStem(CCStr p, CCStr stem) {
    auto pair = splitExt(p);
    return pair.first+stem+pair.second;
}

}


