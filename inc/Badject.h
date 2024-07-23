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
        static bool build(const std::string& bad_bin, const std::string& str_bin);
        
    private:
        uint8_t              cpxor; ///< Computed XOR, fixed to 1 at build-time.
        std::queue<uint16_t> offqe; ///< Queue for bad character index within string.   

        /// @brief Default constructor.
        Badject();

        /// @brief Check and compute the consistant value to XOR with.
        /// @param bad_bin Name for the binary file containing the bad characters.
        /// @return True if a consistant XOR value was found, else return False.
        bool compute_xor(const std::string& bad_bin);

        /// @brief Check and compute XORed content.
        /// @param bad_bin Name for the binary file containing the bad characters.
        /// @param str_bin Name for the binary file wich content has to be XORed.
        /// @return True if succeed, else return False.
        bool compute_str(const std::string& bad_bin, const std::string& str_bin);

        /// @brief Generate file containing consistant value to XOR with.
        void gen_xvl();

        /// @brief Generate file containing XORed content both with files containing offsets.
        void gen_esc(const std::string& bad_bin, const std::string& str_bin);

        //TODO gen_off()

        Badject(const Badject& orig); ///< = delete
        Badject& operator=(const Badject& orig); ///< = delete
};

inline Badject::Badject():
    cpxor(1),
    offqe()
{
}

#endif