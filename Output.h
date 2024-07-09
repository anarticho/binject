#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "stdfw.h"

/// @brief Output structure to handle string, number of occurences and process to output it to standart stream.
struct Output
{
    uint8_t nb;         ///< Total number of occurences that str shall be outputed.
    std::string str;    ///< String to be outputed.

    /// @brief Default constructor.
    Output();

    /// @brief Output process from built parameters.
    void process();
};

inline Output::Output():
    nb(1),
    str()
{
}

#endif