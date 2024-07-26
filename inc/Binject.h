#ifndef BINJECT_H_
#define BINEJCT_H_

#include <Builder.h>

/// @brief 
class Binject: private Args, private Builder
{
    public:
        /// @brief Default constructor.
        /// @param argc     Total number of arguments (including path, not explicitly inserted).
        /// @param argv     Array of arguments (from main entry point).
        explicit Binject(int argc, char* argv[]);

        /// @brief Initialize by building arguments into Output objects.
        /// @return False if an error occured, else return True.
        bool init();

        /// @brief Process all the Output objects from queue.
        void step();

    private:
        /// File for to redirect output content (optionnal, zero-length at build-time).
        Output out_file;

        /// Queue used at checking bad characters to record flags.
        std::vector<std::string> bad_flg;

        /// @brief Check for provided chain to detect badcharacters.
        /// @return Always false.
        bool get_cb();

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