#ifndef BADJECT_H_
#define BADJECT_H_

#include <stdfw.h>

/// @brief Class to handle -bd flag mechanism.
class Badject
{
    public:
        /// @brief Build outputs for provided parameters.
        /// @param bad_bin Name for the binary file containing the bad characters.
        /// @param str_bin Name for the binary file wich content has to be XORed.
        /// @return True if operation succeed, else return False.
        static bool build(std::string bad_bin, std::string str_bin);
        
    private:
        /// @brief Parameters to build.
        struct Params
        {
            std::string bads;   ///< Bad characters.
            std::string mods;   ///< String to be XORed.
        };

        Params               parms; ///< Bad characters and string to be XORed.
        uint8_t              cpxor; ///< Computed XOR, fixed to 1 at build-time.
        std::queue<uint16_t> offqe; ///< Queue for bad character index within string.   

        /// @brief Default constructor.
        /// @param params Provided binary file's names to build with.
        explicit Badject(Params params);

        /// @brief Check and compute the consistant value to XOR with.
        /// @return True if a consistant XOR value was found, else return False.
        bool compute_xor();

        /// @brief Check and compute XORed content.
        /// @return True if succeed, else return False.
        bool compute_str();

        /// @brief Generate all output for this flag.
        void gen_output();

        /// @brief Generate file containing consistant value to XOR with.
        void gen_xvl();

        /// @brief Generate file containing XORed content both with files containing offsets.
        void gen_esc();

        //TODO gen_off()

        Badject(const Badject& orig); ///< = delete
        Badject& operator=(const Badject& orig); ///< = delete
};

inline Badject::Badject(Params params):
    parms(params),
    cpxor(1),
    offqe()
{
}

#endif