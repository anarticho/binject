#ifndef FLAGS_H_
#define FLAGS_H_

#include <stdfw.h>

enum Flag_id    ///< Flags used by binject.
{
    /// @brief Enhanced flags, shall be the first one.
    enh_outf = 0,   ///< [file_name], to generate output on file from format flags.
    enh_gnbd,       ///< [badf_name] [strf_name], to generate XOR, escaped and offset files.
    enh_ckbd,       ///< No parameter, check for all binary files from execution location.  

    /// @brief Format flag, with only one argument [data].
    fmt_str,        ///< [data] as ASCII string.
    fmt_hex,        ///< [data] as HEX string.
    fmt_addr,       ///< [data] as address (compiler-dependant), in x86-64, 8 bytes as little-endian.
    
    /// @brief Format flag, with additional parameter to repeat the output [n] [data].
    fmt_nstr,
    fmt_nhex,
    fmt_naddr,
    
    in_file,

    nb_flags
};

struct Flags
{
    public:
        typedef const char* type;           ///< Returned type (null terminated string).
        static const type* get(Flag_id id);       ///< Retrieve non-terminated ASCII string from provided flag.

    private:
        Flags(); ///< = delete
        Flags(const Flags& orig); ///< = delete
        Flags& operator=(const Flags& orig); ///< = delete
};

#endif