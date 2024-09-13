
#pragma once

#include <string>
#include <utility> // pair

#include <ctime>
#include "./oserrors.h"


namespace Path {

const char sep =
#ifdef _WIN32
 '\\'
#else
 '/'
#endif
;


using CCStr = const char* const;
using CStr = const char*;


std::string normalizePathEnd(CCStr p);

std::string stripPathEnd(CCStr p);

std::string joinPath(CCStr a, CCStr b);



std::pair<std::string, std::string> splitExt(CCStr p);
std::string appendStem(CCStr p, CCStr stem);


namespace is
{
    bool dir(CCStr p);
} // namespace is



namespace Dir {

std::string Data();
const std::string& Cwd();

}
namespace info
{
  // returns time_t
  namespace timet
  {
    /// @throw std::system_error
    time_t lastModification(CCStr file);
    
  } // namespace timet
  

}
}