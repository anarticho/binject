#ifndef STDFW_H_
#define STDFW_H_

#include <algorithm> // for std::reverse
#include <cstdint>      // for native types (uint8_t)
#include <cstring>      // for std::strlen
#include <functional>   // for std::function
#include <fstream>      // for std::fstream
#include <iostream>     // for std::iostream
#include <map>          // for std::map
#include <queue>        // for std::queue
#include <regex>        // for std::regex_match
#include <string>       // for std::stoi (and std::string obviously)

namespace File
{
    using namespace std;

    static const ios_base::openmode wr_mode = 
        ios_base::out | ios_base::binary | ios_base::trunc;
}

#endif