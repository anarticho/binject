#ifndef BINJECT_H_
#define BINEJCT_H_

#include "Builder.h"

/// @brief 
class Binject
{
    public:
        /// @brief Constructor.
        /// @param argc     Number of arguments (from main entry point).
        /// @param argv     Array of arguments (from main entry point).
        explicit Binject(int argc, char* argv[]);

        /// @brief Process Output from queue.
        /// @return True if there is still content on the queue, else return False.
        bool step();

    private:
        enum Build_state    ///< States to parse arguments.
        {
            st_flag,    ///< Check and parse first byte expected to contain flags.
            st_mult,    ///< Check and parse multiplier ASCII string.
            st_str,     ///< Just parse 
        };

        Builder::Outputs outputs;   ///< Queue to store Output objects to be processed on step.
        Builder builder;            ///< Object to build queue of Output to be processed.

        /// @brief Build queue of Output objects from provided parameters.
        /// @param ptr  Array of pointers for arguments to be built.
        /// @param end  Pointer to the last element to be built.
        /// @return False if an error occured, else return True.
        bool build(char** ptr, const char* const end);

        Binject(const Binject& orig); ///< = delete
        Binject& operator=(const Binject& orig); ///< = delete
};

#endif