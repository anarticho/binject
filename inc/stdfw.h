#ifndef STDFW_H_
#define STDFW_H_

#include <algorithm>    // for std::reverse
#include <cstdint>      // for native types (uint8_t)
#include <cstring>      // for std::strlen
#include <filesystem>   // for std::path and std::create directory
#include <functional>   // for std::function
#include <fstream>      // for std::fstream
#include <iostream>     // for std::iostream
#include <map>          // for std::map
#include <queue>        // for std::queue
#include <regex>        // for std::regex_match
#include <string>       // for std::stoi (and std::string obviously)
#include <system_error> // for std::error_code

static const uint8_t u64_sz8 = UINT64_WIDTH / UINT8_WIDTH;  // 8 bytes length (64-bits)  

#endif