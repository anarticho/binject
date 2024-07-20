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

        Builder::Outputs outputs;   ///< Queue to store Output objects to be processed on step.
        Builder          builder;   ///< Object to build queue of Output to be processed.
        std::string      outfile;   ///< File for to redirect output content (optionnal, zero-length at build-time).

        /// Map of functions to process the first flag.
        std::map<std::string, std::function<bool (char***)> > func_map;

        /// @brief Check, parse and process -bd flag from provided parameter.
        /// @param ptr_arg  Pointer to the argument as ASCII string.
        /// @return False if process failed, else return True.
        bool get_bd(char*** ptr_arg);

        /// @brief Check, parse and process -of flag from provided parameter.
        /// @param ptr_arg  Pointer to the argument as ASCII string.
        /// @return False if process failed, else return True.
        bool get_of(char*** ptr_arg);

        /// @brief Check first argument and forward to first parameter or to the builder.
        /// @param ptr_arg  Pointer to the argument as ASCII string.
        /// @return False if process failed, else return True.
        bool check(char*** ptr_arg);

        /// @brief Check for output file to redirect parsed flags on it.
        /// @param ofstr    Output file stream.
        /// @return False if file was opened and correctly redirected, else return True.
        bool get_ostr(std::ofstream& ofstr);

        /// @brief Build queue of Output objects from provided parameters.
        /// @param ptr  Array of null terminated strings to be built.
        /// @return False if an error occured, else return True.
        bool build(char** ptr);

        Binject(const Binject& orig); ///< = delete
        Binject& operator=(const Binject& orig); ///< = delete
};

#endif