#ifndef BADJECT_H_
#define BADJECT_H_

#include "stdfw.h"

class Badject
{
    public:
        static bool build(std::string bad_bin, std::string str_bin);
        
    private:
        uint8_t     cpxor;  ///< Computed XOR, fixed to 1 at build-time.

        Badject();
        bool chck_str(std::string bad_bin, std::string str_bin);
        bool init_xor(std::string bad_bin);
        void gen_out();

        Badject(const Badject& orig); ///< = delete
        Badject& operator=(const Badject& orig); ///< = delete
};

inline Badject::Badject():
    cpxor(1)
{
}

#endif