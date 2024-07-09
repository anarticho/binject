#include "Binject.h"

/// Main entry point for the application
/// \param[in] argc     Total number of arguments within ::argv array.
/// \param[in] argv     Array of arguments.
int main(int argc, char* argv[])
{
    /// Arguments are coming through [-flag] [data] format as:
    /// - [-flag] an ASCII string beginning with '-' and flag character(s).
    /// - [data] an ASCII string to be interpreted from provided flag.
    
    /// Flag determine the way [data] will be outputed as:
    /// - 's' as ASCII string.
    /// - 'x' as hexadecim string.

    /// Additionaly, [num] can be appended between [-flag] and [data] to repeat
    /// the output. It's format shall be a strictly positive integer.

    /// Some examples:
    /// > binject -s ABCD               will output "ABCD"
    /// > binject -x 41424344           will output "ABCD"
    /// > binject -s AB -x 4344         will output "ABCD"
    /// > binject -ns 2 A -nx 2 42      will output "AABB"

    //TODO Add -v flag to have std::cout writing log/errors to provided TTY.

    Binject binject(argc, argv);
    while(binject.step());

    return 1;     
}