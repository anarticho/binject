#include <Binject.h>

/// Main entry point for the application
/// \param[in] argc     Total number of arguments within ::argv array.
/// \param[in] argv     Array of arguments.
int main(int argc, char* argv[])
{
    //TODO Add -v flag to have std::cout writing log/errors to provided TTY.

    Binject binject(argc, argv);
    binject.step();

    return 1;     
}