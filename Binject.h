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

        /// @brief Process all the Output objects from queue.
        void step();

    private:
        enum Build_state    ///< States to parse arguments.
        {
            st_flag,    ///< Check and parse first byte expected to contain flags.
            st_mult,    ///< Check and parse multiplier ASCII string.
            st_str,     ///< Just parse 
        };

        Builder::Outputs outputs;       ///< Queue to store Output objects to be processed on step.
        Builder          builder;       ///< Object to build queue of Output to be processed.
        std::string      outfile;   ///< File for to redirect output content (optionnal, zero-length at build-time).

        /// @brief Check for output file to redirect parsed flags on it.
        /// @param ofstr    Output file stream.
        /// @return False if file was opened and correctly redirected, else return True.
        bool to_file(std::ofstream& ofstr);

        /// @brief Initialize output file if -of flag is detected in a valid format.
        /// @param start    Pointer to the array of null terminated strings for arguments to be built.
        /// @return True if -of flag is correct, or if it was not detected, else return false.
        bool init(char*** start);

        /// @brief Build queue of Output objects from provided parameters.
        /// @param ptr  Array of null terminated strings to be built.
        /// @return False if an error occured, else return True.
        bool build(char** ptr);

        Binject(const Binject& orig); ///< = delete
        Binject& operator=(const Binject& orig); ///< = delete
};

#endif