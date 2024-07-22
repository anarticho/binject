#ifndef BADJECT_H_
#define BADJECT_H_

#include <stdfw.h>

class Badject
{
    public:
        static bool build(std::string bad_bin, std::string str_bin);
        
    private:
        struct Params
        {
            std::string bads;   ///< Bad characters.
            std::string mods;   ///< String to be XORed.
        };
        Params      parms;  ///< Bad characters and string to be XORed.
        uint8_t     cpxor;  ///< Computed XOR, fixed to 1 at build-time.
        std::queue<uint16_t>  
                    offqe;  ///< Queue for bad character index within string.   

        explicit Badject(Params params);
        bool compute_xor();
        bool compute_str();

        void gen_output();
        void gen_xvl();
        void gen_esc();

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