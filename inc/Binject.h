#ifndef BINJECT_H_
#define BINEJCT_H_

#include <Builder.h>

/// @brief 
class Binject: private Builder
{
    public:
        /// @brief Constructor.
        /// @param argc     Total number of arguments (including path, not explicitly inserted).
        /// @param argv     Array of arguments (from main entry point).
        explicit Binject(int argc, char* argv[]);

        /// @brief Process all the Output objects from queue.
        void step();

    private:
        /// File for to redirect output content (optionnal, zero-length at build-time).
        Output out_file;

        /// @brief Check, parse and process -bd flag from provided parameter.
        /// @return False if process failed, else return True.
        bool get_bd();

        /// @brief Check, parse and process -of flag from provided parameter.
        /// @return False if process failed, else return True.
        bool get_of();

        /// @brief Check first argument and forward to first parameter or to the builder.
        /// @return False if process failed, else return True.
        bool check();

        Binject(const Binject& orig); ///< = delete
        Binject& operator=(const Binject& orig); ///< = delete
};

#endif